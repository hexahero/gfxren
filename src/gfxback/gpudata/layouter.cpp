#include "layouter.h"

namespace GFXREN {

	LAYOUTER::LAYOUTER() : _descriptorArrayID { 0 } {}

	void LAYOUTER::generate_descriptor_array() {

		GL_TRY(glGenVertexArrays(1, &_descriptorArrayID));
	}

	void LAYOUTER::bind_descriptor_array() {

		if (!_descriptorArrayID) {

			PRINT_ERROR("descriptorArrayID: no id associated (descriptorArrayID == 0)", true, true);
			return;
		}

		GL_TRY(glBindVertexArray(_descriptorArrayID));
	}

	void LAYOUTER::unbind_descriptor_array() {

		GL_TRY(glBindVertexArray(0));
	}

	void LAYOUTER::describe_shader_attribute(
		GLuint attributeIndex,
		GLint numberOfComponentsAssociated,
		GLsizei stride,
		size_t offset,
		GLenum dataType,
		GLboolean isNormalized
	)
	{

		if (!_descriptorArrayID) {

			PRINT_ERROR("descriptorArrayID: no id associated (descriptorArrayID == 0)", true, true);
			return;
		}

		GL_TRY(glVertexAttribPointer(
			attributeIndex,
			numberOfComponentsAssociated,
			dataType,
			isNormalized,
			stride,
			reinterpret_cast<GLvoid*>(offset)
		));

		enable_shader_attribute(attributeIndex);

	}

	void LAYOUTER::enable_shader_attribute(GLuint attributeIndex) {
		
		GL_TRY(glEnableVertexAttribArray(attributeIndex));
	}

	void LAYOUTER::disable_shader_attribute(GLuint attributeIndex) {
		
		GL_TRY(glDisableVertexAttribArray(attributeIndex));
	}

	void LAYOUTER::delete_descriptor_array() {

		GL_TRY(glDeleteVertexArrays(1, &_descriptorArrayID));
	}

	GLuint LAYOUTER::get_id() const {

		return _descriptorArrayID;
	}

}