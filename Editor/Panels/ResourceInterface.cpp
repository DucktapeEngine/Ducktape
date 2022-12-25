#include <Panels/ResourceInterface.h>

namespace DT
{
    void MaterialInterface::Init()
    {
        iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "material.png"))->id;
    }

    void MaterialInterface::OpenInspect(RID rid)
    {
        openedMaterial.Load(rid);
        filename = ResourceManager::GetPath(rid).filename().string();
    }

    void MaterialInterface::Inspect()
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Material");

        ImGui::Separator();

        ImGui::Color("diffuse color", &openedMaterial.Data()->diffuseColor);
        ImGui::Color("specular color", &openedMaterial.Data()->specularColor);
        ImGui::Color("ambient color", &openedMaterial.Data()->ambientColor);
        ImGui::DragFloat("shininess", &openedMaterial.Data()->shininess);
        ImGui::Resource("texture", &openedMaterial.Data()->texture);

        std::string textureType = "Unknown type";
        switch (openedMaterial.Data()->textureType)
        {
        case Texture::Type::DIFFUSE:
            textureType = "Diffuse";
            break;
        case Texture::Type::HEIGHT:
            textureType = "Height";
            break;
        case Texture::Type::NORMAL:
            textureType = "Normal";
            break;
        case Texture::Type::SPECULAR:
            textureType = "Specular";
            break;
        }

        int currentTextureType = openedMaterial.Data()->textureType;
        ImGui::SliderInt("Texture Type", &currentTextureType, 0, 3, textureType.c_str());
        openedMaterial.Data()->textureType = (Texture::Type)currentTextureType;

        // ImGui:: something for texture type
        ImGui::Resource("shader", &openedMaterial.Data()->shader);
    }

    void MaterialInterface::CloseInspect()
    {
        openedMaterial.Save();
    }

    void TextureInterface::Init()
    {
        iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "image.png"))->id;
    }

    void TextureInterface::OpenInspect(RID rid)
    {
        openedTexture.Load(rid);
        filename = ResourceManager::GetPath(rid).filename().string();
    }

    void TextureInterface::Inspect()
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Texture");

        ImGui::Separator();

        ImGui::Image((ImTextureID)(uintptr_t)openedTexture.Data()->id, ImVec2(ImGui::GetWindowContentRegionWidth(), openedTexture.Data()->height * (ImGui::GetWindowContentRegionWidth() / openedTexture.Data()->width)), ImVec2(0, 1), ImVec2(1, 0));
    }

    void TextureInterface::CloseInspect()
    {
        openedTexture.Save();
    }

    void MeshInterface::Init()
    {
        iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "mesh.png"))->id;
    }

    void MeshInterface::OpenInspect(RID rid)
    {
        openedMesh.Load(rid);
        filename = ResourceManager::GetPath(rid).filename().string();
    }

    void MeshInterface::Inspect()
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Mesh");

        ImGui::Separator();

        ImGui::Text("materials");
        for (int i = 0; i < openedMesh.Data()->materials.size(); i++)
            ImGui::Resource(std::to_string(i), &openedMesh.Data()->materials[i]);
    }

    void MeshInterface::CloseInspect()
    {
        openedMesh.Save();
    }

    ModelImporter::ModelImporter(std::filesystem::path path)
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

    void ModelImporter::ProcessNode(aiNode *node, const aiScene *scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
            ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene);

        for (unsigned int i = 0; i < node->mNumChildren; i++)
            ProcessNode(node->mChildren[i], scene);
    }

    void ModelImporter::ProcessMesh(aiMesh *mesh, const aiScene *scene)
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
        std::filesystem::path meshFileName = std::filesystem::path(std::string(mesh->mName.C_Str()) + ".dtmesh");

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

    std::vector<RID> ModelImporter::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, Texture::Type textureType)
    {
        std::vector<RID> materialRIDs;
        std::string materialName = mat->GetName().C_Str();

        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
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
            std::string materialFileName = materialName + "-" + typeName + ".dtmaterial";

            std::filesystem::create_directories(modelDir / "Materials");
            std::ofstream out(modelDir / "Materials" / materialFileName);
            out << json(material);

            materialRIDs.push_back(ResourceManager::GetRID(modelDir / "Materials" / materialFileName));
        }

        return materialRIDs;
    }

    void ModelInterface::Init()
    {
        iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "model.png"))->id;
    }

    void ModelInterface::Inspect()
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Model");

        ImGui::Separator();
    }

    void ModelInterface::OpenInspect(RID rid)
    {
        filename = ResourceManager::GetPath(rid).filename().string();
    }

    void ModelInterface::Import(RID rid)
    {
        ModelImporter modelImporter(ResourceManager::GetPath(rid));
    }

    void MarkdownInterface::Init()
    {
        iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "markdown.png"))->id;
    }

    void MarkdownInterface::OpenInspect(RID rid)
    {
        std::ifstream in("file.txt");
        std::stringstream buffer;
        buffer << in.rdbuf();
        data = buffer.str();
        filename = ResourceManager::GetPath(rid).filename().string();
    }

    void MarkdownInterface::Inspect()
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Markdown");

        ImGui::Separator();

        ImGui::TextDisabled("Markdown Viewer yet to be implemented.");
    }

    Interface *ResourceInterface::GetInterface(const std::string &extension)
    {
        if (!HasInterface(extension))
            return nullptr;
        return interfaces[extension];
    }

    bool ResourceInterface::HasInterface(const std::string &extension)
    {
        return interfaces.find(extension) != interfaces.end();
    }

    unsigned int ResourceInterface::GetIcon(const std::string &extension)
    {
        unsigned int iconId = 0;
        Interface *interface = ResourceInterface::GetInterface(extension);
        if (interface != nullptr)
            iconId = interface->iconId;
        if (iconId == 0)
            iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "file.png"))->id;
        return iconId;
    }

    void ResourceInterface::AddDefault()
    {
        RegisterInterface<MaterialInterface>(".mtl", ".dtmaterial");
        RegisterInterface<TextureInterface>(".jpg", ".png", ".jpeg");
        RegisterInterface<ModelInterface>(".obj", ".fbx");
        RegisterInterface<MeshInterface>(".dtmesh");
        RegisterInterface<MarkdownInterface>(".md");
    }
}