#include "lightsource.h"

namespace GFXREN{

	LIGHTSOURCE::LIGHTSOURCE(GFXREN::CAMERA& camera)
		:
		GFXREN::MODEL(
			"Light source",
			GFXREN::UTIL::get_relative_path("gfxren") + "resources/models/hipoly_sphere/sphere.gltf",
			{ 0.0f, 0.0f, 0.0f }
		),
		_shader(
			DEFAULT_DIR"scene/lightsource.vrtx.glsl",
			DEFAULT_DIR"scene/lightsource.pxl.glsl"
		),
		_camera(camera),
		_isLightingOn(true),
		_lightColor({ 1.0f, 1.0f, 1.0f, 1.0f }),
		_lightLinearTerm{ 0.001f },
		_lightQuadraticTerm{ 0.001f }
	{

		set_scale(0.5f, 0.5f, 0.5f);
	}

	void LIGHTSOURCE::enable_lighting() {

		_isLightingOn = true;
	}

	void LIGHTSOURCE::disable_lighting() {

		_isLightingOn = false;
	}

	bool LIGHTSOURCE::is_lighting_on() const {

		return _isLightingOn;
	}

	void LIGHTSOURCE::update(const GFXREN::SHADER& shader) const {

		shader.use();

		shader.set_vec3("cameraPos", _camera.get_position());
		shader.set_vec3("lightPos", get_position());
		shader.set_vec4("lightColor", _lightColor);
		shader.set_float("lightLinear", _lightLinearTerm);
		shader.set_float("lightQuadratic", _lightQuadraticTerm);

	}

	void LIGHTSOURCE::set_light_color(const glm::vec4& color) {

		_lightColor = color;

		_shader.use();
		_shader.set_vec4("lightColor", _lightColor);

	}

	void LIGHTSOURCE::set_light_linear_term(const float linear) {

		_lightLinearTerm = linear;
	}

	void LIGHTSOURCE::set_light_quadratic_term(const float quadratic) {

		_lightQuadraticTerm = quadratic;
	}

	float* LIGHTSOURCE::get_light_linear_term_pointer() {

		return &_lightLinearTerm;
	}

	float* LIGHTSOURCE::get_light_quadratic_term_pointer() {

		return &_lightQuadraticTerm;
	}

	GFXREN::SHADER& LIGHTSOURCE::get_shader() {

		return _shader;
	}

}