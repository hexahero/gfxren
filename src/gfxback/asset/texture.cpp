#include "texture.h"

namespace GFXREN {

	TEXTURE::TEXTURE() 
		:
		_texturePath(),
		_texture(nullptr),
		_textureID(),
		_width(),
		_height(),
		_nrChannels(GFXREN_TEXTURE_COLOUR_FORMAT_RGBA)
	{}

	TEXTURE::TEXTURE(const char* texturePath)
		:
		_texturePath(texturePath),
		_texture(nullptr),
		_textureID(),
		_width(),
		_height(),
		_nrChannels(GFXREN_TEXTURE_COLOUR_FORMAT_RGBA)
	{ 
		construct();
	}

	TEXTURE::TEXTURE(
		const char* texturePath,
		GLenum texMinFilter,
		GLenum texMagFilter,
		GLenum wrapS,
		GLenum wrapT,
		bool mipmap,
		bool flipUVs
	)
		:
		_texturePath(texturePath),
		_texture(nullptr),
		_textureID(),
		_width(),
		_height(),
		_nrChannels(GFXREN_TEXTURE_COLOUR_FORMAT_RGBA)
	{ 
		construct(texMinFilter, texMagFilter, wrapS, wrapT, mipmap, flipUVs);
	}

	void TEXTURE::construct(
		GLenum texMinFilter,
		GLenum texMagFilter,
		GLenum wrapS,
		GLenum wrapT,
		bool mipmap,
		bool flipUVs
	) 
	{

		generate();
		load(_texturePath, flipUVs);

		if (_texture) { 
			
			bind();
			allocate(_width, _height);
			set_params(texMinFilter, texMagFilter, wrapS, wrapT);
			
			if (mipmap)
				GL_TRY(glGenerateMipmap(GL_TEXTURE_2D));
		
		}
		else { 
			
			PRINT_ERROR("TEXTURE LOAD FAILED", false, false);
		}

		free();
		
	}

	void TEXTURE::generate() {

		GL_TRY(glGenTextures(1, &_textureID));
	}

	void TEXTURE::bind() const { 
		
		GL_TRY(glBindTexture(GL_TEXTURE_2D, _textureID));
	}

	void TEXTURE::load(const char* texturePath, bool flipUVs) {

		stbi_set_flip_vertically_on_load(flipUVs);
		_texture = stbi_load(texturePath, &_width, &_height, &_nrChannels, 0);

	}

	void TEXTURE::allocate(GLuint width, GLuint height, GLenum type) {

		GLenum format = GL_RGBA;

		if (_nrChannels == GFXREN_TEXTURE_COLOUR_FORMAT_RED) { format = GL_RED; }
		else if (_nrChannels == GFXREN_TEXTURE_COLOUR_FORMAT_RGB) { format = GL_RGB; }
		else if (_nrChannels == GFXREN_TEXTURE_COLOUR_FORMAT_RGBA) { format = GL_RGBA; }

		GL_TRY(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, _texture));

	}

	void TEXTURE::set_params(GLenum texMinFilter, GLenum texMagFilter, GLenum wrapS, GLenum wrapT) {

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texMinFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texMagFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

	}

	void TEXTURE::free() { 
		
		stbi_image_free(_texture); 
	}

}