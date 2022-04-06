#pragma once

#include <sstream>
#include <fstream>

#include "../util/exceptions.h"

#include <glad.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//Default shader directory path
#define DEFAULT_DIR "../bin/shaders/"

namespace GFXREN {

	class SHADER {
	
	public:

		SHADER();
		SHADER(const char* vertex, const char* fragment, const char* geometry = nullptr);

		void add(const char* vertex, const char* fragment, const char* geometry = nullptr);
		inline void use() const;
		inline unsigned int get_id() const;

		inline void set_mat4(const std::string& name, const glm::mat4& mat) const;
		inline void set_bool(const std::string& name, bool value) const;
		inline void set_int(const std::string& name, int value) const;
		inline void set_float(const std::string& name, float value) const;
		inline void set_float3(const std::string& name, float v1, float v2, float v3) const;
		inline void set_float3(const std::string& name, glm::vec3 v) const;
		inline void set_float4(const std::string& name, float v1, float v2, float v3, float v4) const;
		inline void set_float4(const std::string& name, glm::vec4 v) const;

	private:

		unsigned int shaderProgramID;

		unsigned int compiledVertexShader;
		unsigned int compiledFragmentShader;
		unsigned int compiledGeometryShader;

		void build_shader_program(const char* vertex, const char* fragment, const char* geometry = nullptr);
		unsigned int compile_vertex_shader(const char* vShaderCode);
		unsigned int compile_fragment_shader(const char* fShaderCode);
		unsigned int compile_geometry_shader(const char* gShaderCode);
		unsigned int link_shaders();
		unsigned short check_err(unsigned int shader, const char* type);
		
	};

	void SHADER::use() const {

		glUseProgram(shaderProgramID);
	}

	void  SHADER::set_mat4(const std::string& name, const glm::mat4& mat) const {

		glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void SHADER::set_bool(const std::string& name, bool value) const {

		glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), static_cast<int>(value));
	}

	void SHADER::set_int(const std::string& name, int value) const {

		glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
	}

	void SHADER::set_float(const std::string& name, float value) const {

		glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
	}
			
	void SHADER::set_float3(const std::string& name, float v1, float v2, float v3) const {

		glUniform3f(glGetUniformLocation(shaderProgramID, name.c_str()), v1, v2, v3);
	}

	void SHADER::set_float3(const std::string& name, glm::vec3 v) const {

		glUniform3f(glGetUniformLocation(shaderProgramID, name.c_str()), v.x, v.y, v.z);
	}

	void SHADER::set_float4(const std::string& name, float v1, float v2, float v3, float v4) const {

		glUniform4f(glGetUniformLocation(shaderProgramID, name.c_str()), v1, v2, v3, v4);
	}

	void SHADER::set_float4(const std::string& name, glm::vec4 v) const {

		glUniform4f(glGetUniformLocation(shaderProgramID, name.c_str()), v.x, v.y, v.z, v.w);
	}

}