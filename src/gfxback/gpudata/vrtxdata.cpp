#include "vrtxdata.h"
#include "../asset/mesh.h"

namespace GFXREN {

	VRTXDATA::VRTXDATA() : _vboID { 0 } {}

	void VRTXDATA::generate_vrtx_buff() {

		GL_TRY(glGenBuffers(1, &_vboID));
	}

	void VRTXDATA::bind_vrtx_buff() const {

		if (!_vboID) {

			PRINT_ERROR("vboID: no id associated (vboID == 0)", true, true);
			return;
		}

		GL_TRY(glBindBuffer(GL_ARRAY_BUFFER, _vboID));

	}

	void VRTXDATA::unbind_vrtx_buff() {

		GL_TRY(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VRTXDATA::send_vrtx_data(const std::vector<float>& vertices, GLenum usage) const {

		if (!_vboID) {

			PRINT_ERROR("vboID: no id associated (vboID == 0)", true, true);
			return;
		}

		GL_TRY(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], usage));

	}

	void VRTXDATA::send_vrtx_data(std::vector<GFXREN::VRTX>& vertices, GLenum usage) const {

		if (!_vboID) {

			PRINT_ERROR("vboID: no id associated (vboID == 0)", true, true);
			return;
		}

		GL_TRY(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GFXREN::VRTX), &vertices[0], usage));

	}

	void VRTXDATA::delete_vrtx_buff() {

		GL_TRY(glDeleteBuffers(1, &_vboID));
	}

	GLuint VRTXDATA::get_id() const {

		return _vboID;
	}

}