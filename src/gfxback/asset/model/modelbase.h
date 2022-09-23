#pragma once

#include <vector>

#include "../mesh.h"
#include "../asset.loader.h"
#include "../../util/glerr.hpp"
#include "../../util/filesystem.h"

#include <../gfxback/shader/shader.h>

namespace GFXREN {

    class MODELBASE {

    public:

        MODELBASE(const MODELBASE&) = delete;
        MODELBASE& operator = (const MODELBASE&) = delete;

        // Construction
        MODELBASE();
        MODELBASE(const std::string& path);
        MODELBASE(MODELBASE&& modelbase) noexcept;
        MODELBASE& operator = (MODELBASE&& modelbase) noexcept;

        // Draw model
        void draw(GFXREN::SHADER& shader);

    protected:
        
        // Model data
        std::vector<GFXREN::MESH>   _meshes;
        std::vector<GFXREN::TEX>    _textures;
        
        // Mesh data
        unsigned int _totalVertexCount;
        unsigned int _totalIndexCount;

    };

}