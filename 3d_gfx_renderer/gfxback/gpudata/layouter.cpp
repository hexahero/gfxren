#include "layouter.h"

namespace GFXREN {

	LAYOUTER::LAYOUTER() : descriptorArrayID(0) {}

	LAYOUTER::~LAYOUTER() {

		delete_descriptor_array();
	}

	void LAYOUTER::generate_descriptor_array() {

		glGenVertexArrays(1, &descriptorArrayID);
	}

	void LAYOUTER::bind_descriptor_array() {

		if (!descriptorArrayID) {

			EXCEPTION("descriptorArrayID: no id associated (descriptorArrayID == 0)", true);
			return;
		}

		glBindVertexArray(descriptorArrayID);
	}

	void LAYOUTER::unbind_descriptor_array() {

		glBindVertexArray(0);
	}

	void LAYOUTER::describe_shader_attribute(
												GLuint attributeIndex, 
												GLint numberOfComponentsAssociated,
												GLsizei stride,
												GLuint offset,
												GLenum dataType, 
												GLboolean isNormalized
											) 
	{

		if (!descriptorArrayID) {

			EXCEPTION("descriptorArrayID: no id associated (descriptorArrayID == 0)", true);
			return;
		}

		GL_TRY(glVertexAttribPointer(
										attributeIndex, 
										numberOfComponentsAssociated, 
										dataType, 
										isNormalized, 
										stride *  sizeof(float), 
										reinterpret_cast<GLvoid*>(offset * sizeof(float))
									));

		enable_shader_attribute(attributeIndex);

	}

	void LAYOUTER::enable_shader_attribute(GLuint attributeIndex) {
		
		glEnableVertexAttribArray(attributeIndex);
	}

	void LAYOUTER::disable_shader_attribute(GLuint attributeIndex) {
		
		glDisableVertexAttribArray(attributeIndex);
	}

	void LAYOUTER::delete_descriptor_array() {

		glDeleteVertexArrays(1, &descriptorArrayID);
	}

	unsigned int LAYOUTER::get_id() {

		return descriptorArrayID;
	}

}