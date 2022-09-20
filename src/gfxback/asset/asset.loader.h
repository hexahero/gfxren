#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "texture.h"
#include "../util/filesystem.h"

namespace GFXREN {

	class ASSETLOADER {

    public:
        
        ASSETLOADER(const ASSETLOADER&) = delete;

        // Construction
        ASSETLOADER();

        // Asset loading
        void            load_model(
            const std::string& path,
            std::vector<GFXREN::MESH>*  meshes,
            std::vector<GFXREN::TEX>*   textures
        );
        unsigned int    load_texture(const char* path) const;

    private:

        // Internal logic
        void read_model_files(const std::string& path, bool flipUVs);

        void                        process_node(aiNode* node, const aiScene* scene);
        GFXREN::MESH                process_mesh(aiMesh* mesh, const aiScene* scene);
        std::vector<GFXREN::TEX>    load_material_textures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

        // Asset data
        std::vector<GFXREN::MESH>*  _meshes;
        std::vector<GFXREN::TEX>*   _textures;
        std::string                 _directory;

	};

}