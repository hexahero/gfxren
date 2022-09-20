#include "indxdata.h"

namespace GFXREN {

	INDXDATA::INDXDATA() : _eboID { 0 } {}

	void INDXDATA::generate_indx_buff() {

		GL_TRY(glGenBuffers(1, &_eboID));
	}

	void INDXDATA::bind_indx_buff() {

		if (!_eboID) {

			PRINT_ERROR("eboID: no id associated (eboID == 0)", true, true);
			return;
		}

		GL_TRY(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboID));

	}

	void INDXDATA::unbind_indx_buff() {

		GL_TRY(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void INDXDATA::send_indx_data(const std::vector<unsigned int>& indices, GLenum usage) {

		if (!_eboID) {

			PRINT_ERROR("eboID: no id associated (eboID == 0)", true, true);
			return;
		}

		GL_TRY(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], usage));

	}

	void INDXDATA::delete_indx_buff() {

		GL_TRY(glDeleteBuffers(1, &_eboID));
	}

	GLuint INDXDATA::get_id() const {

		return _eboID;
	}

}