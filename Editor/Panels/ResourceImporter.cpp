#include <Panels/ResourceImporter.h>

namespace DT
{
    void ResourceImporter::Reimport(const std::filesystem::path &path)
    {
        std::string extension = path.extension().string();

        if (!importers.count(extension))
            return;

        importers[extension](path);
    }

    void ResourceImporter::AddImporter(std::string extension, Importer importer)
    {
        importers[extension] = importer;
    }

    void ModelImporter(const std::filesystem::path &path)
    {
        ImportModel model(path);
    }

    ImportModel::ImportModel(std::filesystem::path path)
    {
        modelName = path.filename().replace_extension().string();

        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }

        directory = path.parent_path();

        ProcessNode(scene->mRootNode, scene);
    }

    void ImportModel::ProcessNode(aiNode *node, const aiScene *scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
            ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene);

        for (unsigned int i = 0; i < node->mNumChildren; i++)
            ProcessNode(node->mChildren[i], scene);
    }

    void ImportModel::ProcessMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;

            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;
            }

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;

                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoords = vec;

                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.tangent = vector;

                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.bitangent = vector;
            }
            else
                vertex.texCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<RID> materials;
        std::vector<RID> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse", Texture::Type::DIFFUSE);
        materials.insert(materials.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<RID> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specular", Texture::Type::SPECULAR);
        materials.insert(materials.end(), specularMaps.begin(), specularMaps.end());
        std::vector<RID> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "normal", Texture::Type::NORMAL);
        materials.insert(materials.end(), normalMaps.begin(), normalMaps.end());
        std::vector<RID> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "height", Texture::Type::HEIGHT);
        materials.insert(materials.end(), heightMaps.begin(), heightMaps.end());

        std::filesystem::path modelDir = directory / modelName;
        std::filesystem::path meshFileName = std::filesystem::path(std::string(mesh->mName.C_Str()) + ".mesh.json");

        std::filesystem::create_directories(modelDir);

        Mesh resultMesh;
        resultMesh.vertices = vertices;
        resultMesh.indices = indices;
        resultMesh.materials.resize(materials.size());
        for (int i = 0; i < materials.size(); i++)
            resultMesh.materials[i].rid = materials[i];

        std::ofstream out(modelDir / meshFileName);
        out << json(resultMesh);
    }

    std::vector<RID> ImportModel::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, Texture::Type textureType)
    {
        std::vector<RID> materialRIDs;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            std::string materialName = mat->GetName().C_Str();

            aiString str;
            mat->GetTexture(type, i, &str);
            std::string textureName(str.C_Str());

            Material material;
            aiColor3D color(1.f, 1.f, 1.f);
            mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
            material.diffuseColor = {color.r, color.g, color.b};
            mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
            material.specularColor = {color.r, color.g, color.b};
            mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
            material.ambientColor = {color.r, color.g, color.b};
            material.texture.rid = ResourceManager::GetRID(directory / textureName);
            material.shader.rid = ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Shaders" / "Default.glsl");
            material.textureType = textureType;

            std::filesystem::path modelDir = directory / modelName;
            std::string materialFileName = materialName + "-" + typeName + ".material.json";

            std::filesystem::create_directories(modelDir / "Materials");
            std::ofstream out(modelDir / "Materials" / materialFileName);
            out << json(material);

            materialRIDs.push_back(ResourceManager::GetRID(modelDir / "Materials" / materialFileName));
        }
        return materialRIDs;
    }
}