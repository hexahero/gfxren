#pragma once

#include <stb_image.h>
#include "../context/glctx.h"

namespace GFXREN {

	class TEXTURE {

	public:
		
		TEXTURE() = default;
		TEXTURE(const char* texturePath);
		TEXTURE(

			const char* texturePath,
			GLenum texMinFilter,
			GLenum texMagFilter,
			GLenum wrapS,
			GLenum wrapT,
			bool mipmap,
			bool flip

		);

		void add(const char* texturePath);
		void construct(

			GLenum texMinFilter = GL_LINEAR,
			GLenum texMagFilter = GL_LINEAR,
			GLenum wrapS = GL_REPEAT,
			GLenum wrapT = GL_REPEAT,
			bool mipmap = true,
			bool flip = true

		);
		inline void bind() const;

		inline const char* get_path() const;
		inline unsigned int get_id() const;
		
		inline int get_width() const;
		inline int get_height() const;

	private:

		const char* texturePath;
		unsigned int textureID;
		unsigned char* texture;

		int width;
		int height;
		int nrChannels;

		void generate();
		void set_params(
		
			GLenum texMinFilter,
			GLenum texMagFilter,
			GLenum wrapS,
			GLenum wrapT
		
		);
		void load(const char* texturePath, bool flip = true);
		void allocate(GLuint width, GLuint height, GLenum type = GL_UNSIGNED_BYTE);
		void free();

	};

}