#pragma once

#include <vector>
#include <glm.hpp>

#include <stb_image.h>

#include "../gpudata/layouter.h"
#include "../gpudata/vrtxdata.h"
#include "../gpudata/indxdata.h"
#include "../shader/shader.h"

#define MAX_BONE_INFLUENCE 4

namespace GFXREN {

    struct VRTX {

        glm::vec3 _position;
		glm::vec2 _texCoords;
        glm::vec3 _normal;

        glm::vec3 _tangent;
        glm::vec3 _bitangent;

        int     _boneIDs[MAX_BONE_INFLUENCE];
        float   _wights[MAX_BONE_INFLUENCE];

    };

    struct TEX {

        unsigned int    _id;
        std::string     _type;
        std::string     _path;

    };

    class MESH {

    public:

        MESH() = delete;
        MESH(const MESH&) = delete;
        MESH& operator = (const MESH&) = delete;

        // Construction/Setup
        MESH(std::vector<GFXREN::VRTX>& vertices, std::vector<unsigned int>& indices, std::vector<GFXREN::TEX>& textures);
        MESH(MESH&& mesh) noexcept;
        MESH& operator = (MESH&& mesh) noexcept;

        // Control
        void engage(GFXREN::SHADER shader);
        void draw() const;
        
        // Get/Set
        inline const std::vector<GFXREN::VRTX>& get_vertices() const;
        inline const std::vector<unsigned int>& get_indices() const;
        inline const std::vector<GFXREN::TEX>&  get_textures() const;

        inline unsigned int get_vertex_count() const;
        inline unsigned int get_index_count() const;

    private:

        void setup();
        
        // Mesh data
        std::vector<GFXREN::VRTX>   _vertices;
        std::vector<unsigned int>   _indices;
        std::vector<GFXREN::TEX>    _textures;
        
        unsigned int _vertexCount;
        unsigned int _indexCount;

        // Buffer/GPU data
        GFXREN::LAYOUTER _dataLayoutDescriptor;
        GFXREN::VRTXDATA _vrtxData;
        GFXREN::INDXDATA _indxData;

    };
    
    const std::vector<GFXREN::VRTX>& MESH::get_vertices() const {

        return _vertices;
    }

    const std::vector<unsigned int>& MESH::get_indices() const {
        
        return _indices;
    }

    const std::vector<GFXREN::TEX>& MESH::get_textures() const {

        return _textures;
    }

    unsigned int MESH::get_vertex_count() const {

        return _vertexCount;
    }

    unsigned int MESH::get_index_count() const {
        
        return _indexCount;
    }

}