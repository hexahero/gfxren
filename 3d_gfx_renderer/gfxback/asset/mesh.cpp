#include "mesh.h"

namespace GFXREN {

    MESH::MESH(std::vector<VRTX> vertices, std::vector<unsigned int> indices, std::vector<TEX> textures) {

        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setup_mesh();

    }

    void MESH::setup_mesh() {

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VRTX), &vertices[0], GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VRTX), (void*)0); //cast with reinterpret_cast
		
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VRTX), (void*)offsetof(VRTX, TexCoords)); //cast with reinterpret_cast
		
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(TEX), (void*)offsetof(VRTX, Normal)); //cast with reinterpret_cast

        glBindVertexArray(0);

    }

    void MESH::draw(GFXREN::SHADER shader) {
        
        stbi_set_flip_vertically_on_load(true);
        glEnable(GL_DEPTH_TEST);
        shader.use();

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;

        for (unsigned short int i = 0; i < textures.size(); i++) {

            glActiveTexture(GL_TEXTURE0 + i); 
           
            std::string number;
            std::string name = textures[i].type;

            if (name == "texture_diffuse") number = std::to_string(diffuseNr++);
            else if (name == "texture_specular") number = std::to_string(specularNr++);

            shader.set_float(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);

        }

        glActiveTexture(GL_TEXTURE0);

        GL_TRY(glBindVertexArray(vao));
        GL_TRY(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0));
        GL_TRY(glBindVertexArray(0));

    }

}