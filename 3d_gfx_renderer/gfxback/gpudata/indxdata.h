#pragma once

#include <vector>
#include "../context/glctx.h"

namespace GFXREN {

	class INDXDATA {

	public:

		INDXDATA();
	   ~INDXDATA();

		void generate_indx_buff();
		void bind_indx_buff();
		static void unbind_indx_buff();
		void send_indx_data(const std::vector<unsigned int>& indices, GLenum usage = GL_STATIC_DRAW);
		void delete_indx_buff();
		unsigned int get_id();

	private:

		unsigned int eboID;

	};

}