#pragma once

#include <vector>

#include "../context/glctx.h"
#include "../util/glerr.hpp"

namespace GFXREN {

	// Forward declaration to avoid circular dependency
	struct VRTX; 

	class VRTXDATA {

	public:

		VRTXDATA();

	    void		generate_vrtx_buff();
		void		bind_vrtx_buff() const;
		static void unbind_vrtx_buff();
		void		send_vrtx_data(const std::vector<float>& vertices, GLenum usage = GL_STATIC_DRAW) const;
		void		send_vrtx_data(std::vector<GFXREN::VRTX>& vertices, GLenum usage = GL_STATIC_DRAW) const;
		void		delete_vrtx_buff();
		GLuint		get_id() const;
		
	private:

		GLuint _vboID;

	};

}