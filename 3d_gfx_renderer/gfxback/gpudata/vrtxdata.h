#pragma once

#include <vector>
#include "../context/glctx.h"

namespace GFXREN {

	class VRTXDATA {

	public:

		VRTXDATA();
	   ~VRTXDATA();

	    void generate_vrtx_buff();
		void bind_vrtx_buff() const;
		static void unbind_vrtx_buff();
		void send_vrtx_data(const std::vector<float>& vertices, GLenum usage = GL_STATIC_DRAW) const;
		void delete_vrtx_buff();
		unsigned int get_id() const;
		
	private:

		unsigned int vboID;

	};

}