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

	void RENDERER::draw_model(MODEL& model, SHADER& shader, bool wireframe) const {

		// Check if model should not currently be drawn
		if (model.is_hidden()) return;

		// Engage shader
		shader.use();

		// Update model's internal states
		model.update(shader);

		// Check for color mode and update lighting data
		switch(model.get_pixel_mode()) {

			case GFXREN_SOLID_COLOR:
				shader.set_int("pixelMode", GFXREN_SOLID_COLOR);
				shader.set_vec4("solidColor", model.get_solid_color());
				shader.set_float("ambientIntensity", model.get_ambient_light_intensity());
				shader.set_float("specularIntensity", model.get_specularity());
				break;

			case GFXREN_SURFACE_NORMALS:
				shader.set_int("pixelMode", GFXREN_SURFACE_NORMALS);
				shader.set_float("ambientIntensity", 1.0f);
				shader.set_float("specularIntensity", 0.0f);
				break;

			case GFXREN_TEXTURE_ONLY:
				shader.set_int("pixelMode", GFXREN_TEXTURE_ONLY);
				shader.set_float("ambientIntensity", 1.0f);
				shader.set_float("specularIntensity", 0.0f);
				break;

			case GFXREN_ILLUMINATED:
				shader.set_int("pixelMode", GFXREN_ILLUMINATED);
				shader.set_float("ambientIntensity", model.get_ambient_light_intensity());
				shader.set_float("specularIntensity", model.get_specularity());
				break;

			default:
				PRINT_ERROR("INCORRECT PIXEL MODE", true, false);
				break;

		}

		// Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Check for wireframe mode
		if (wireframe)
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