#pragma once

#include "../context/glctx.h"

namespace GFXREN {

	class LAYOUTER {

	public:

		LAYOUTER();
	   ~LAYOUTER();

		void generate_descriptor_array();
		void bind_descriptor_array();
		static void unbind_descriptor_array();
		void describe_shader_attribute(
										GLuint attributeIndex,
										GLint numberOfComponentsAssociated,
										GLsizei stride,
										GLuint offset,
										GLenum dataType = GL_FLOAT,
										GLboolean isNormalized = GL_FALSE
									  );
		void enable_shader_attribute(GLuint attributeIndex);
		void disable_shader_attribute(GLuint attributeIndex);
		void delete_descriptor_array();
		unsigned int get_id();

	private:

		unsigned int descriptorArrayID;

	};

}