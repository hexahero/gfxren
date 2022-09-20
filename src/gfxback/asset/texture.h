#pragma once

#include <stb_image.h>
#include "../context/glctx.h"
#include "../util/glerr.hpp"

#define GFXREN_TEXTURE_COLOUR_FORMAT_RED	1 
#define GFXREN_TEXTURE_COLOUR_FORMAT_RGB	3
#define GFXREN_TEXTURE_COLOUR_FORMAT_RGBA	4

namespace GFXREN {

	class TEXTURE {

	public:
		
		TEXTURE(const TEXTURE&) = delete;

		// Construction/Setup
		TEXTURE();
		TEXTURE(const char* texturePath);
		TEXTURE(
			const char* texturePath,
			GLenum texMinFilter,
			GLenum texMagFilter,
			GLenum wrapS,
			GLenum wrapT,
			bool mipmap,
			bool flipUVs
		);
		void construct(
			GLenum texMinFilter = GL_LINEAR_MIPMAP_LINEAR,
			GLenum texMagFilter = GL_LINEAR,
			GLenum wrapS = GL_REPEAT,
			GLenum wrapT = GL_REPEAT,
			bool mipmap = true,
			bool flipUVs = false
		);

		// Get/Set
		inline const char*	get_path() const;
		inline unsigned int get_id() const;
		
		inline int get_width() const;
		inline int get_height() const;

	private:

		// Internal texture logic
		void generate();
		void bind() const;
		void load(const char* texturePath, bool flipUVs);
		void allocate(GLuint width, GLuint height, GLenum type = GL_UNSIGNED_BYTE);
		void set_params(GLenum texMinFilter, GLenum texMagFilter, GLenum wrapS, GLenum wrapT);
		void free();

		// General data
		const char*		_texturePath;
		unsigned char*	_texture;
		unsigned int	_textureID;

		int _width;
		int _height;
		int _nrChannels;

	};

	const char* TEXTURE::get_path() const { 
		
		return _texturePath; 
	}

	unsigned int TEXTURE::get_id() const { 
		
		return _textureID; 
	};

	int TEXTURE::get_width() const { 
		
		return _width; 
	}

	int TEXTURE::get_height() const { 
		
		return _height; 
	}

}