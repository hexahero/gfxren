#pragma once

#include <vector>
#include <glm.hpp>

#include "../context/glctx.h"
#include "../shader/shader.h"
#include "texture.h"

namespace GFXREN {

    struct VRTX {

        glm::vec3 Position;
		glm::vec2 TexCoords;
        glm::vec3 Normal;

    };

    struct TEX {

        unsigned int id;
        std::string type;
        std::string path;

    };

    class MESH {

    private:

        unsigned int vao;
        unsigned int vbo;
        unsigned int ebo;

        void setup_mesh();

    public:

        std::vector<GFXREN::VRTX> vertices;
        std::vector<unsigned int> indices;
        std::vector<GFXREN::TEX> textures;

        MESH() = default;
        MESH(std::vector<GFXREN::VRTX> vertices, std::vector<unsigned int> indices, std::vector<GFXREN::TEX> textures);

        void draw(GFXREN::SHADER shader);

    };

}