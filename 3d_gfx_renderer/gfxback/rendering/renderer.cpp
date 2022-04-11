#include "renderer.h"

namespace GFXREN {

	RENDERER::RENDERER() { 
		
		glEnable(GL_DEPTH_TEST);
		clear(GFXREN_BLACK);

	}

	void RENDERER::draw_model(MODEL& model, SHADER& shader, bool wireframe, bool isTextured) const {

		shader.use();

		model.bind();
		model.update(shader);

		if (isTextured) 
			model.enable_textures(shader);
		else
			model.disable_textures(shader);

		if (wireframe == true)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else 
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		model.draw();

	}

	void RENDERER::clear() const { 
		
		GL_TRY(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)) 
	}
	
	void RENDERER::clear(float r, float g, float b, float a) const {
		
		glClearColor(r, g, b, a);
		GL_TRY(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
	
	}

}