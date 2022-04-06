#include "model.h"

namespace GFXREN {

	MODEL::MODEL(
					const char* name,
					const char* texturePath,
					glm::vec3 mdlPos,
					const std::vector<float>& vertices,
					const std::vector<unsigned int>& indices
				)
		:
		name(name),
		texturePath(texturePath),
		mdlPos(mdlPos)
	{
		
		this->vertices = vertices;
		this->indices = indices;

		unsigned int tempVertSize = static_cast<unsigned int>(vertices.size());
		vertexCount = tempVertSize / 5;
		indexCount = static_cast<unsigned int>(indices.size());
		sizeInBytes = tempVertSize * sizeof(float);

		modelTransformMtrx	= 
			 translateMtrx	= 
				 scaleMtrx	= 
			  rotationMtrx	= glm::mat4(1.0f);

		setup();
		print_model_data();
		
	}

	void MODEL::setup() {

		dataLayoutDescriptor.generate_descriptor_array();
		dataLayoutDescriptor.bind_descriptor_array();

		vrtxData.generate_vrtx_buff();
		vrtxData.bind_vrtx_buff();
		vrtxData.send_vrtx_data(vertices);

		if (!indices.empty()) {

			indxData.generate_indx_buff();
			indxData.bind_indx_buff();
			indxData.send_indx_data(indices);

		}
		
		//Vertex positions
		dataLayoutDescriptor.describe_shader_attribute(0, 3, 5, 0);

		//Vertex texture coords
		dataLayoutDescriptor.describe_shader_attribute(1, 2, 5, 3);

		dataLayoutDescriptor.unbind_descriptor_array();

		texture.add(texturePath);
		texture.construct();

	}

	void MODEL::bind() {

		texture.bind();
		dataLayoutDescriptor.bind_descriptor_array();

	}

	void MODEL::draw() {

		if (!indices.empty()) 
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, 0);
		else 
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));

	}

	void MODEL::update(GFXREN::SHADER& shader) {

		translateMtrx = glm::translate(translateMtrx, mdlPos);
		scaleMtrx = glm::scale(scaleMtrx, mdlScale);
		modelTransformMtrx = translateMtrx * rotationMtrx * scaleMtrx;

		shader.set_mat4("model", modelTransformMtrx);

		modelTransformMtrx =
			 translateMtrx =
			     scaleMtrx =
			  rotationMtrx = glm::mat4(1.0f);

	}

	void MODEL::enable_attribute(GLuint index) {

		dataLayoutDescriptor.enable_shader_attribute(index);
	}

	void MODEL::disable_attribute(GLuint index) {

		dataLayoutDescriptor.disable_shader_attribute(index);
	}

	void MODEL::enable_textures(GFXREN::SHADER& shader) {

		shader.use();
		shader.set_bool("isTextured", true);

	}

	void MODEL::disable_textures(GFXREN::SHADER& shader) {

		shader.use();
		shader.set_bool("isTextured", false);

	}

	void MODEL::move(float x, float y, float z) {

		mdlPos.x += x;
		mdlPos.y += y;
		mdlPos.z += z;

	}

	void MODEL::scale(float x, float y, float z) {

		mdlScale.x += x;
		mdlScale.y += y;
		mdlScale.z += z;

	}

	void MODEL::rotate(float speed, glm::vec3 angle) {

		rotationMtrx = glm::rotate(rotationMtrx, float(glfwGetTime()) * speed, angle);

	}

	unsigned int MODEL::get_vrtx_count() const { 

		return vertexCount; 
	}

	inline void MODEL::print_model_data() const {

		std::stringstream ss;

		ss << "<|MODEL INFO|>\n"
			<< "\"" << name << "\"\n"
			<< "Mesh Size (bytes) [" << sizeInBytes << "]\n"
			<< "Vertex Count [" << vertexCount << "]\n"
			<< "Texture Path [" << texturePath << "]\n";

		std::cout << ss.str() << '\n';

	}

}