#pragma once

#include "../context/glctx.h"
#include "../shader/shader.h"
#include "../asset/model/model.h"
#include "../util/glerr.hpp"
#include "colors.h"
#include "canvas.h"

#define GFXREN_SOLID_COLOR			1
#define GFXREN_SURFACE_NORMALS		2
#define GFXREN_TEXTURE_ONLY			3
#define GFXREN_ILLUMINATED			4

namespace GFXREN {

	class RENDERER {

	public:

	    RENDERER();

		void draw_model(MODEL& model, SHADER& shader, bool wireframe) const;
		void draw_shader_canvas(CANVAS& canvas, SHADER& shader, bool wireframe = false) const ;

		void clear() const;
		void clear(float* colour) const;
		void clear(float r, float g, float b, float a) const;

	};

}