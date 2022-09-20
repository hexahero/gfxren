#include "renderer.h"

#ifdef PROFILE
#include <Tracy.hpp>
#include <TracyOpenGL.hpp>
#endif

namespace GFXREN {

	RENDERER::RENDERER() { 
		
		glEnable(GL_DEPTH_TEST);
		clear(GFXREN_BLACK);

	}

	void RENDERER::draw_model(MODEL& model, SHADER& shader, bool wireframe, bool isTextured) const {
		
		// Engage shader
		shader.use();

		// Update model internal states
		model.update(shader);

		// Check for textureless mode
		if (isTextured) 
			model.enable_textures(shader);
		else
			model.disable_textures(shader);

		// Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Check for wireframe mode
		if (wireframe == true)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else 
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Make draw call
		model.draw(shader);

		// Cleanup
		glDisable(GL_BLEND);

		// Profiling data
		#ifdef PROFILE
			TracyGpuZone("indexed draw");
		#endif

	}

	void RENDERER::draw_shader_canvas(CANVAS& canvas, SHADER& shader, bool wireframe) const {

		// Engage shader
		shader.use();

		// Update canvas' internal states
		canvas.update(shader);

		// Check for the wireframe mode
		if (wireframe == true)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Make draw call
		canvas.draw();

		// Profiling data
		#ifdef PROFILE
			TracyGpuZone("shader canvas draw");
		#endif

	}

	void RENDERER::clear() const {
		
		GL_TRY(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)) 
	}
	
	void RENDERER::clear(float* colour) const {

		glClearColor(colour[0], colour[1], colour[2], colour[3]);
		GL_TRY(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))

	}

	void RENDERER::clear(float r, float g, float b, float a) const {
		
		glClearColor(r, g, b, a);
		GL_TRY(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
	
	}

}