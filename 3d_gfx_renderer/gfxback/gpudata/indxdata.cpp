#include "indxdata.h"

namespace GFXREN {

	INDXDATA::INDXDATA() : eboID(0) {}

	INDXDATA::~INDXDATA() {

		delete_indx_buff();
	}

	void INDXDATA::generate_indx_buff() {

		glGenBuffers(1, &eboID);
	}

	void INDXDATA::bind_indx_buff() {

		if (!eboID) {

			EXCEPTION("eboID: no id associated (eboID == 0)", true);
			return;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

	}

	void INDXDATA::unbind_indx_buff() {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void INDXDATA::send_indx_data(const std::vector<unsigned int>& indices, GLenum usage) {

		if (!eboID) {

			EXCEPTION("eboID: no id associated (eboID == 0)", true);
			return;
		}

		GL_TRY(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], usage));

	}

	void INDXDATA::delete_indx_buff() {

		glDeleteBuffers(1, &eboID);
	}

	unsigned int INDXDATA::get_id() {

		return eboID;
	}

}