#include "texture.h"

namespace GFXREN {

	TEXTURE::TEXTURE(const char* texturePath) 
		:
		texturePath(texturePath)
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
		bool flip
	
	)
		:
		texturePath(texturePath)
	{ construct(texMinFilter, texMagFilter, wrapS, wrapT, mipmap, flip); }

	void TEXTURE::add(const char* texturePath) { this->texturePath = texturePath; }

	void TEXTURE::construct(

		GLenum texMinFilter,
		GLenum texMagFilter,
		GLenum wrapS,
		GLenum wrapT,
		bool mipmap,
		bool flip

	) {

		generate();
		set_params(texMinFilter, texMagFilter, wrapS, wrapT);
		load(texturePath, flip);

		if (texture) { 
			
			allocate(width, height);
			if (mipmap) { glGenerateMipmap(GL_TEXTURE_2D); }
		
		}
		else { EXCEPTION("TEXTURE LOAD FAILED", false); }

		free();
		
	}

	void TEXTURE::bind() const { glBindTexture(GL_TEXTURE_2D, textureID); }

	const char* TEXTURE::get_path() const { return texturePath; }

	unsigned int TEXTURE::get_id() const { return textureID; };

	int TEXTURE::get_width() const { return width; }

	int TEXTURE::get_height() const { return height; }

	void TEXTURE::generate() { glGenTextures(1, &textureID); }

	void TEXTURE::set_params(

		GLenum texMinFilter,
		GLenum texMagFilter,
		GLenum wrapS,
		GLenum wrapT

	) {

		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texMinFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texMagFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

	}

	void TEXTURE::load(const char* texturePath, bool flip) {

		stbi_set_flip_vertically_on_load(flip);
		texture = stbi_load(texturePath, &width, &height, &nrChannels, 0);

	}

	void TEXTURE::allocate(GLuint width, GLuint height, GLenum type) {

		GLenum format = GL_RGBA;

		if (nrChannels == 1) { format = GL_RED; }
		else if (nrChannels == 3) { format = GL_RGB; }
		else if (nrChannels == 4) { format = GL_RGBA; }

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, texture);

	}

	void TEXTURE::free() { stbi_image_free(texture); }

}