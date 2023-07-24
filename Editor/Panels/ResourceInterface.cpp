#include <Panels/ResourceInterface.h>

namespace DT
{
    void MaterialInterface::Init(ContextPtr& ctx)
    {
        iconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "material.png"), ctx)->id;
    }

    void MaterialInterface::OpenInspect(RID rid, ContextPtr& ctx)
    {
        openedMaterial.Load(rid, ctx);
        filename = ctx.resourceManager->GetPath(rid).filename().string();
    }

    void MaterialInterface::Inspect(ContextPtr &ctx)
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Material");

        ImGui::Separator();

        ImGui::Color("diffuse color", &openedMaterial.data->diffuseColor);
        ImGui::Color("specular color", &openedMaterial.data->specularColor);
        ImGui::Color("ambient color", &openedMaterial.data->ambientColor);
        ImGui::DragFloat("shininess", &openedMaterial.data->shininess);
        ImGui::Resource("texture", &openedMaterial.data->texture, ctx);

        std::string textureType = "Unknown type";
        switch (openedMaterial.data->textureType)
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

        int currentTextureType = openedMaterial.data->textureType;
        ImGui::SliderInt("Texture Type", &currentTextureType, 0, 3, textureType.c_str());
        openedMaterial.data->textureType = (Texture::Type)currentTextureType;

        // ImGui:: something for texture type
        ImGui::Resource("shader", &openedMaterial.data->shader, ctx);
    }

    void MaterialInterface::CloseInspect(ContextPtr &ctx)
    {
        openedMaterial.Save(ctx);
    }

    void TextureInterface::Init(ContextPtr &ctx)
    {
        iconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "image.png"), ctx)->id;
    }

    void TextureInterface::OpenInspect(RID rid, ContextPtr& ctx)
    {
        openedTexture.Load(rid, ctx);
        filename = ctx.resourceManager->GetPath(rid).filename().string();
    }

    void TextureInterface::Inspect(ContextPtr &ctx)
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Texture");

        ImGui::Separator();

        ImGui::Image((ImTextureID)(uintptr_t)openedTexture.data->id, ImVec2(ImGui::GetWindowContentRegionWidth(), openedTexture.data->height * (ImGui::GetWindowContentRegionWidth() / openedTexture.data->width)), ImVec2(0, 1), ImVec2(1, 0));
    }

    void TextureInterface::CloseInspect(ContextPtr &ctx)
    {
        openedTexture.Save(ctx);
    }

    void MeshInterface::Init(ContextPtr &ctx)
    {
        iconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "mesh.png"), ctx)->id;
    }

    void MeshInterface::OpenInspect(RID rid, ContextPtr& ctx)
    {
        openedMesh.Load(rid, ctx);
        filename = ctx.resourceManager->GetPath(rid).filename().string();
    }

    void MeshInterface::Inspect(ContextPtr &ctx)
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Mesh");

        ImGui::Separator();

        ImGui::Text("materials");
        for (int i = 0; i < openedMesh.data->materials.size(); i++)
            ImGui::Resource(std::to_string(i), &openedMesh.data->materials[i], ctx);
    }

    void MeshInterface::CloseInspect(ContextPtr &ctx)
    {
        openedMesh.Save(ctx);
    }

    ModelImporter::ModelImporter(std::filesystem::path path, ContextPtr &ctx)
    {
        modelName = path.filename().replace_extension().string();

        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "[ERR] [ASSIMP] " << importer.GetErrorString() << std::endl;
            return;
        }

        directory = path.parent_path();

        ProcessNode(scene->mRootNode, scene, ctx);
    }

    void ModelImporter::ProcessNode(aiNode *node, const aiScene *scene, ContextPtr &ctx)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
            ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene, ctx);

        for (unsigned int i = 0; i < node->mNumChildren; i++)
            ProcessNode(node->mChildren[i], scene, ctx);
    }

    void ModelImporter::ProcessMesh(aiMesh *mesh, const aiScene *scene, ContextPtr &ctx)
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
        std::vector<RID> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse", Texture::Type::DIFFUSE, ctx);
        materials.insert(materials.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<RID> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specular", Texture::Type::SPECULAR, ctx);
        materials.insert(materials.end(), specularMaps.begin(), specularMaps.end());
        std::vector<RID> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "normal", Texture::Type::NORMAL, ctx);
        materials.insert(materials.end(), normalMaps.begin(), normalMaps.end());
        std::vector<RID> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "height", Texture::Type::HEIGHT, ctx);
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

    std::vector<RID> ModelImporter::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, Texture::Type textureType, ContextPtr &ctx)
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
            material.texture.rid = ctx.resourceManager->GetRID(directory / textureName);
            material.shader.rid = ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Shaders" / "Default.glsl");
            material.textureType = textureType;

            std::filesystem::path modelDir = directory / modelName;
            std::string materialFileName = materialName + "-" + typeName + ".dtmaterial";

            std::filesystem::create_directories(modelDir / "Materials");
            std::ofstream out(modelDir / "Materials" / materialFileName);
            out << json(material);

            materialRIDs.push_back(ctx.resourceManager->GetRID(modelDir / "Materials" / materialFileName));
        }

        return materialRIDs;
    }

    void ModelInterface::Init(ContextPtr &ctx)
    {
        iconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "model.png"), ctx)->id;
    }

    void ModelInterface::Inspect(ContextPtr &ctx)
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Model");

        ImGui::Separator();
    }

    void ModelInterface::OpenInspect(RID rid, ContextPtr& ctx)
    {
        filename = ctx.resourceManager->GetPath(rid).filename().string();
    }

    void ModelInterface::Import(RID rid, ContextPtr &ctx)
    {
        ModelImporter modelImporter(ctx.resourceManager->GetPath(rid), ctx);
    }

    void MarkdownInterface::Init(ContextPtr &ctx)
    {
        iconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "markdown.png"), ctx)->id;
    }

    void MarkdownInterface::OpenInspect(RID rid, ContextPtr& ctx)
    {
        std::ifstream in("file.txt");
        std::stringstream buffer;
        buffer << in.rdbuf();
        data = buffer.str();
        filename = ctx.resourceManager->GetPath(rid).filename().string();
    }

    void MarkdownInterface::Inspect(ContextPtr &ctx)
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

    unsigned int ResourceInterface::GetIcon(const std::string &extension, ContextPtr &ctx)
    {
        unsigned int iconId = 0;
        Interface *interface = ResourceInterface::GetInterface(extension);
        if (interface != nullptr)
            iconId = interface->iconId;
        if (iconId == 0)
            iconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "file.png"), ctx)->id;
        return iconId;
    }

    void ResourceInterface::AddDefault(ContextPtr &ctx)
    {
        RegisterInterface<MaterialInterface>({".mtl", ".dtmaterial"}, ctx);
        RegisterInterface<TextureInterface>({".jpg", ".png", ".jpeg"}, ctx);
        RegisterInterface<ModelInterface>({".obj", ".fbx"}, ctx);
        RegisterInterface<MeshInterface>({".dtmesh"}, ctx);
        RegisterInterface<MarkdownInterface>({".md"}, ctx);
    }
}