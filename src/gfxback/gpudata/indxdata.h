#pragma once

#include <vector>

#include "../context/glctx.h"
#include "../util/glerr.hpp"

namespace GFXREN {

	class INDXDATA {

	public:

		INDXDATA();

		void		generate_indx_buff();
		void		bind_indx_buff();
		static void unbind_indx_buff();
		void		send_indx_data(const std::vector<unsigned int>& indices, GLenum usage = GL_STATIC_DRAW);
		void		delete_indx_buff();
		GLuint		get_id() const;

	private:

		GLuint _eboID;

	};

}