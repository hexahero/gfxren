#include "mesh.h"

namespace GFXREN {

    MESH::MESH(std::vector<VRTX>& vertices, std::vector<unsigned int>& indices, std::vector<TEX>& textures) {

        _vertices = std::move(vertices);
        _indices = std::move(indices);
        _textures = std::move(textures);

        _vertexCount = static_cast<unsigned int>(_vertices.size());
        _indexCount = static_cast<unsigned int>(_indices.size());

        setup();

    }

    MESH::MESH(MESH&& mesh) noexcept
		:
		_vertices(std::move(mesh._vertices)),
        _indices(std::move(mesh._indices)),
        _textures(std::move(mesh._textures)),
        _dataLayoutDescriptor(mesh._dataLayoutDescriptor),
        _vrtxData(mesh._vrtxData),
        _indxData(mesh._indxData),
        _vertexCount(mesh.get_vertex_count()),
        _indexCount(mesh.get_index_count())
	{

        mesh._vertices.clear();
        mesh._indices.clear();
        mesh._textures.clear();

        mesh._dataLayoutDescriptor.~LAYOUTER();
        mesh._vrtxData.~VRTXDATA();
        mesh._indxData.~INDXDATA();

    }

    MESH& MESH::operator = (MESH&& mesh) noexcept {

        if (this != &mesh) {

            _vertices = std::move(mesh._vertices);
            _indices = std::move(mesh._indices);
            _textures = std::move(mesh._textures);

            _dataLayoutDescriptor = mesh._dataLayoutDescriptor;
            _vrtxData = mesh._vrtxData;
            _indxData = mesh._indxData;

            _vertexCount = mesh.get_vertex_count();
            _indexCount = mesh.get_index_count();

            mesh._vertices.clear();
            mesh._indices.clear();
            mesh._textures.clear();

            mesh._dataLayoutDescriptor.~LAYOUTER();
            mesh._vrtxData.~VRTXDATA();
            mesh._indxData.~INDXDATA();

        }

        return *this;
    }

    void MESH::setup() {

        // Generate and bind VAO
        _dataLayoutDescriptor.generate_descriptor_array();
        _dataLayoutDescriptor.bind_descriptor_array();

        // Generate and bind VBO
        _vrtxData.generate_vrtx_buff();
        _vrtxData.bind_vrtx_buff();
        _vrtxData.send_vrtx_data(_vertices);

        // Generate and bind EBO
        _indxData.generate_indx_buff();
        _indxData.bind_indx_buff();
        _indxData.send_indx_data(_indices);

        // Set vertex attribute pointers
        _dataLayoutDescriptor.describe_shader_attribute(0, 3, sizeof(VRTX), (0));
        _dataLayoutDescriptor.describe_shader_attribute(1, 2, sizeof(VRTX), (offsetof(VRTX, _texCoords)));
        _dataLayoutDescriptor.describe_shader_attribute(2, 3, sizeof(TEX), (offsetof(VRTX, _normal)));

        // Unbind vao and buffers
        _dataLayoutDescriptor.unbind_descriptor_array();
        _indxData.unbind_indx_buff();
        _vrtxData.unbind_vrtx_buff();

    }

    void MESH::engage(GFXREN::SHADER shader) {

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;

        for (unsigned short int i = 0; i < _textures.size(); i++) {

            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string name = _textures[i]._type;

            if (name == "texture_diffuse") number = std::to_string(diffuseNr++);
            else if (name == "texture_specular") number = std::to_string(specularNr++);

            shader.set_float(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, _textures[i]._id);

        }

        glActiveTexture(GL_TEXTURE0);

        _dataLayoutDescriptor.bind_descriptor_array();

    }

    void MESH::draw() const {

        GL_TRY(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indexCount), GL_UNSIGNED_INT, 0));
        GL_TRY(glBindVertexArray(0));

    }

}