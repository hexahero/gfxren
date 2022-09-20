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
        

        ///////////////////////////////////////////////////////////////////////////////
        std::string print_normals() {

            std::string nrmls;

            for (auto& mesh : _meshes) {

                for (int i = 0; i != mesh.get_vertices().size(); ++i) {

                    float x = mesh.get_vertices().at(i)._normal.x;
                    float y = mesh.get_vertices().at(i)._normal.y;
                    float z = mesh.get_vertices().at(i)._normal.z;

                    //std::cout << x << ' ' << y << ' ' << z << '\n';
                    std::string n = std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(z) + '\n';
                    nrmls += n;

                }

            }

            return nrmls;
        }
        ///////////////////////////////////////////////////////////////////////////////


    protected:
        
        // Model data
        std::vector<GFXREN::MESH> _meshes;
        std::vector<GFXREN::TEX> _textures;
        
        // Mesh data
        unsigned int _totalVertexCount;
        unsigned int _totalIndexCount;

    };

}