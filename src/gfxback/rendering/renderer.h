#pragma once

#include "../context/glctx.h"
#include "../shader/shader.h"
#include "../asset/model/model.h"
#include "../util/glerr.hpp"
#include "colours.h"
#include "canvas.h"

namespace GFXREN {

	class RENDERER {

	public:

	    RENDERER();

		void draw_model(MODEL& model, SHADER& shader, bool wireframe, bool isTextured = true) const;
		void draw_shader_canvas(CANVAS& canvas, SHADER& shader, bool wireframe = false) const ;

		void clear() const;
		void clear(float* colour) const;
		void clear(float r, float g, float b, float a) const;

	};

}