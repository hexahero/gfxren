#include "vrtxdata.h"

namespace GFXREN {

	VRTXDATA::VRTXDATA() : vboID(0) {}

	VRTXDATA::~VRTXDATA() {

		delete_vrtx_buff();
	}

	void VRTXDATA::generate_vrtx_buff() {

		glGenBuffers(1, &vboID);
	}

	void VRTXDATA::bind_vrtx_buff() const {

		if (!vboID) {

			EXCEPTION("vboID: no id associated (vboID == 0)", true);
			return;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vboID);

	}

	void VRTXDATA::unbind_vrtx_buff() {

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VRTXDATA::send_vrtx_data(const std::vector<float>& vertices, GLenum usage) const {

		if (!vboID) {

			EXCEPTION("vboID: no id associated (vboID == 0)", true);
			return;
		}

		GL_TRY(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], usage));

	}

	void VRTXDATA::delete_vrtx_buff() {

		glDeleteBuffers(1, &vboID);
	}

	unsigned int VRTXDATA::get_id() const {

		return vboID;
	}

}