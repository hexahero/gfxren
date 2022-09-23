#pragma once

#include "modelbase.h"

namespace GFXREN {

	class MODEL : public GFXREN::MODELBASE {

	public:

		MODEL() = delete;
		MODEL(const MODEL&) = delete;
		MODEL& operator = (const MODEL&) = delete;

		// Construct/Setup
		MODEL(
			const std::string&	name,
			const std::string&	modelPath,
			glm::vec3			mdlPos = { 0.0f, 0.0f, 0.0f }
		);
		MODEL(MODEL&& model) noexcept;
		MODEL& operator = (MODEL&& model) noexcept;

		// Control
		void hide();
		void show();
		bool is_hidden() const;

		void update(const GFXREN::SHADER& shader);
		void reset_transform_matrices();
		
		// Transformations
		void move(float x, float y, float z);
		void set_position(float x, float y, float z);
		void scale(float x, float y, float z);
		void set_scale(float x, float y, float z);
		void rotate(float speed, const glm::vec3& angle);

		// Get/Set
		unsigned int	get_vrtx_count() const;
		std::string		get_name() const;
		inline void		print_model_data() const;

		glm::vec3		get_position() const;

		float			get_ambient_light_intensity() const;
		float			get_specularity() const;
		unsigned int	get_pixel_mode() const;

		void set_ambient_light_intensity(float ambientIntensity);
		void set_specularity(float specularIntensity);
		void set_pixel_mode(unsigned int pixelMode);
		
	private:

		// General data
		std::string _name;
		std::string _modelPath;

		// Transformation and display data
		glm::vec3 _mdlPos;
		glm::vec3 _mdlScale;
		glm::vec3 _mdlAngle;

		glm::mat4 _modelTransformMtrx;
		glm::mat4 _translateMtrx;
		glm::mat4 _scaleMtrx;
		glm::mat4 _rotationMtrx;

		bool _isHidden;

		// Lighting & material data
		float _ambientIntensity;
		float _specularIntensity;

		unsigned int _pixelMode;

	};

}