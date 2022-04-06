#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <sstream>
#include <utility>

#include "../gpudata/layouter.h"
#include "../gpudata/vrtxdata.h"
#include "../gpudata/indxdata.h"

#include "mesh.h"
#include "texture.h"

namespace GFXREN {

	class MODEL {

	public:

		MODEL(
				const char* name,
				const char* texturePath,
				glm::vec3 mdlPos,
				const std::vector<float>& vertices,
				const std::vector<unsigned int>& indices = std::vector<unsigned int>()
			);

		//Control
		void setup();
		void bind();
		void draw();
		void disable_attribute(GLuint index);
		void enable_attribute(GLuint index);
		void enable_textures(GFXREN::SHADER& shader);
		void disable_textures(GFXREN::SHADER& shader);
		void update(GFXREN::SHADER& shader);
		
		//Transformations
		void move(float x, float y, float z);
		void scale(float x, float y, float z);
		void rotate(float speed, glm::vec3 angle);

		//Getters/Setters
		unsigned int get_vrtx_count() const;
		inline void print_model_data() const;

	private:

		//General data
		const char* name;
		const char* texturePath;

		//GPU data
		GFXREN::LAYOUTER dataLayoutDescriptor;
		GFXREN::VRTXDATA vrtxData;
		GFXREN::INDXDATA indxData;
		GFXREN::TEXTURE texture;

		//Vertex data
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		
		unsigned int vertexCount;
		unsigned int indexCount;
		unsigned int sizeInBytes;

		//Transformation data
		glm::vec3 mdlPos;
		glm::vec3 mdlScale;
		glm::vec3 mdlAngle;

		glm::mat4 modelTransformMtrx;
		glm::mat4 translateMtrx;
		glm::mat4 scaleMtrx;
		glm::mat4 rotationMtrx;

	};

}