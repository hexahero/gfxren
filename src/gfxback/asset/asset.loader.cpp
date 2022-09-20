#include "asset.loader.h"

namespace GFXREN {

    ASSETLOADER::ASSETLOADER()
        :
        _meshes(nullptr),
        _textures(nullptr)
    {}

    void ASSETLOADER::load_model(
        const std::string& path,
        std::vector<GFXREN::MESH>* meshes,
        std::vector<GFXREN::TEX>* textures
    ) {

        _meshes = meshes;
        _textures = textures;
        _directory = path.substr(0, path.find_last_of('/'));

        std::string extension = GFXREN::UTIL::get_file_extension(path);
        bool flipUVs = false;

        if (extension == "gltf") flipUVs = true;

        read_model_files(path, flipUVs);

        _meshes = nullptr;
        _textures = nullptr;
        _directory.clear();

    }

    void ASSETLOADER::read_model_files(const std::string& path, bool flipUVs) {

        int doUVflip = 0;
        if (flipUVs) doUVflip = aiProcess_FlipUVs;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(
            path, 
            aiProcess_Triangulate       | 
            aiProcess_GenSmoothNormals  | 
            aiProcess_CalcTangentSpace  |
            doUVflip
        );

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {

            PRINT_ERROR((
                "ASSIMP: " +
                static_cast<std::string>(importer.GetErrorString()) + 
                " Make sure that the name of the root directory is \"gfxren\""
            ).c_str(), true, false);

            return;
        }

        // Process nodes recursively
        process_node(scene->mRootNode, scene);

    }

    void ASSETLOADER::process_node(aiNode* node, const aiScene* scene) {

        // Process current node meshes
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {

            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            _meshes->emplace_back(process_mesh(mesh, scene));

        }

        // Process child nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++) {

            // Recursive call
            process_node(node->mChildren[i], scene);
        }

    }

    GFXREN::MESH ASSETLOADER::process_mesh(aiMesh* mesh, const aiScene* scene) {

        // Temp mesh data vectors
        std::vector<GFXREN::VRTX> vertices;
        std::vector<unsigned int> indices;
        std::vector<GFXREN::TEX> textures;

        // Iterate over mesh's vertices and acquire their data
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

            GFXREN::VRTX vertex;
            glm::vec3 vector; 

            // Extracting vertex coordinates
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex._position = vector;

            // Extracting normals if any
            if (mesh->HasNormals()) {

                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex._normal = vector;

            }

            // Extracting (if any) texture attributes
            if (mesh->mTextureCoords[0]) {

                glm::vec2 vec;

                // Coordinates
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex._texCoords = vec;

                // Tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex._tangent = vector;

                // Bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex._bitangent = vector;

            }
            else
                vertex._texCoords = glm::vec2(0.0f, 0.0f);

            vertices.emplace_back(vertex);
        }

        // Iterate over faces and extract indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {

            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++) {

                indices.emplace_back(face.mIndices[j]);
            }

        }

        // Process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // Diffuse maps
        std::vector<GFXREN::TEX> diffuseMaps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // Specular maps
        std::vector<GFXREN::TEX> specularMaps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        // Normal maps
        std::vector<GFXREN::TEX> normalMaps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        // Height maps
        std::vector<GFXREN::TEX> heightMaps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        // Return extracted mesh
        return GFXREN::MESH(vertices, indices, textures);
    }

    std::vector<GFXREN::TEX> ASSETLOADER::load_material_textures(aiMaterial* mat, aiTextureType type, const std::string& typeName) {
        
        std::vector<GFXREN::TEX> texturesTemp;

        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {

            aiString str;
            mat->GetTexture(type, i, &str);

            // Check to avoid texture multiple loading
            bool skip = false;
            for (unsigned int j = 0; j < _textures->size(); j++) {

                if (std::strcmp(_textures->at(j)._path.data(), str.C_Str()) == 0) {

                    texturesTemp.emplace_back(_textures->at(j));
                    skip = true;
                    
                    break;
                }

            }

            if (!skip) {

                GFXREN::TEX texture;

                texture._id = load_texture(str.C_Str());
                texture._type = typeName;
                texture._path = str.C_Str();

                texturesTemp.emplace_back(texture);
                _textures->emplace_back(texture);

            }

        }

        return texturesTemp;
    }

    unsigned int ASSETLOADER::load_texture(const char* path) const {

        // Acquire texture path
        std::string filename = std::string(path);
        filename = _directory + '/' + filename;
        
        // Load and setup texture
        GFXREN::TEXTURE texture(filename.c_str());

        return texture.get_id();
    }

}