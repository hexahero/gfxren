#pragma once

#include "../context/glctx.h"
#include "../shader/shader.h"
#include "../asset/model.h"

#define GFXREN_WHITE	1.0f,   1.0f,   1.0f,   1.0
#define GFXREN_BLACK	0.0f,   0.0f,   0.0f,   1.0
#define GFXREN_PURPLE	0.250f, 0.066f, 0.245f, 1.0

namespace GFXREN {

	class RENDERER {

	public:

	    RENDERER();

		void draw_model(MODEL& model, SHADER& shader, bool wireframe, bool isTextured = true) const;

		void clear() const;
		void clear(float r, float g, float b, float a) const;

	};

}