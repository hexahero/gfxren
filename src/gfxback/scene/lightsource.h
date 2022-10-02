#pragma once

#include "camera.h"
#include "../rendering/renderer.h"
#include "../shader/shader.h"
#include "../asset/model/model.h"

namespace GFXREN {

	class LIGHTSOURCE : public GFXREN::MODEL {
	
	public:

		LIGHTSOURCE() = delete;
		LIGHTSOURCE(const LIGHTSOURCE&) = delete;
		LIGHTSOURCE& operator = (const LIGHTSOURCE&) = delete;
		
		LIGHTSOURCE(GFXREN::CAMERA& camera);

		void enable_lighting();
		void disable_lighting();
		bool is_lighting_on() const;

		void	update(const GFXREN::SHADER& shader) const;

		void	set_light_color(const glm::vec4& color);
		void	set_light_linear_term(const float linear);
		void	set_light_quadratic_term(const float quadratic);

		float*	get_light_linear_term_pointer();
		float*	get_light_quadratic_term_pointer();

		GFXREN::SHADER&	get_shader();

	private:

		GFXREN::SHADER	_shader;
		GFXREN::CAMERA& _camera;

		bool _isLightingOn;

		glm::vec4	_lightColor;
		float		_lightLinearTerm;
		float		_lightQuadraticTerm;

	};

}