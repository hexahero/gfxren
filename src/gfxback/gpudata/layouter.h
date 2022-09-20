#pragma once

#include "../context/glctx.h"
#include "../util/glerr.hpp"

namespace GFXREN {

	class LAYOUTER {

	public:

		LAYOUTER();

		void		generate_descriptor_array();
		void		bind_descriptor_array();
		static void unbind_descriptor_array();
		void		describe_shader_attribute(
			GLuint attributeIndex,
			GLint numberOfComponentsAssociated,
			GLsizei stride,
			size_t offset,
			GLenum dataType = GL_FLOAT,
			GLboolean isNormalized = GL_FALSE
		);
		void		enable_shader_attribute(GLuint attributeIndex);
		void		disable_shader_attribute(GLuint attributeIndex);
		void		delete_descriptor_array();
		GLuint		get_id() const;

	private:

		GLuint _descriptorArrayID;

	};

}