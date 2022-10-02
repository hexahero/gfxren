#include "model.h"
#include "../../rendering/renderer.h"

namespace GFXREN {

	MODEL::MODEL(
		const std::string& name,
		const std::string& modelPath,
		glm::vec3 mdlPos
	)
		:
		MODELBASE(modelPath),
		_name(name),
		_modelPath(modelPath),
		_mdlPos(mdlPos),
		_mdlScale({ 0.0f, 0.0f, 0.0f }),
		_mdlAngle({ 0.0f, 0.0f, 0.0f }),
		_isHidden(false),
		_ambientIntensity{ 0.5f },
		_specularIntensity{ 0.5f },
		_pixelMode{ GFXREN_ILLUMINATED },
		_solidColor{ 0.0f, 1.0f, 0.0f, 1.0f }
	{

		reset_transform_matrices();
		set_scale(1.0f, 1.0f, 1.0f);
		print_model_data();

	}

	MODEL::MODEL(MODEL&& model) noexcept
		:
		_name(model._name),
		_modelPath(model._modelPath),
		_mdlPos(model._mdlPos),
		_mdlScale(model._mdlScale),
		_mdlAngle(model._mdlAngle),
		_isHidden(false),
		_ambientIntensity(model._ambientIntensity),
		_specularIntensity(model._specularIntensity),
		_pixelMode{ model._pixelMode },
		_solidColor{ 0.15f, 0.15f, 0.15f, 1.0f },
		GFXREN::MODELBASE(std::move(model))
	{

		reset_transform_matrices();
		model.~MODEL();

	}

	MODEL& MODEL::operator = (MODEL&& model) noexcept {

		if (this != &model) {

			_name = model._name;
			_modelPath = model._modelPath;

			_mdlPos = model._mdlPos;
			_mdlScale = model._mdlScale;
			_mdlAngle = model._mdlAngle;

			_ambientIntensity = model._ambientIntensity;
			_specularIntensity = model._specularIntensity;

			_isHidden = model._isHidden;
			_pixelMode = model._pixelMode;
			_solidColor = model._solidColor;

			GFXREN::MODELBASE::operator = (std::move(model));

			reset_transform_matrices();
			model.~MODEL();

		}

		return *this;
	}

	void MODEL::hide() {

		_isHidden = true;
	}

	void MODEL::show() {

		_isHidden = false;
	}

	bool MODEL::is_hidden() const {
		
		return _isHidden;
	}

	void MODEL::update(const GFXREN::SHADER& shader) {

		_translationMtrx = glm::translate(_translationMtrx, _mdlPos);
		_scaleMtrx = glm::scale(_scaleMtrx, _mdlScale);
		_modelTransformMtrx = _translationMtrx * _rotationMtrx * _scaleMtrx;

		glm::mat3 modelTransposeOfInverse = glm::transpose(glm::inverse(_modelTransformMtrx));

		shader.set_mat4("model", _modelTransformMtrx);
		shader.set_mat3("modelTransposeOfInverse", modelTransposeOfInverse);

		reset_transform_matrices();

	}

	void MODEL::reset_transform_matrices() {
		
		_modelTransformMtrx	=
		_translationMtrx		=
		_scaleMtrx			=
		_rotationMtrx		= glm::mat4(1.0f);

	}

	void MODEL::move(float x, float y, float z) {

		_mdlPos.x += x;
		_mdlPos.y += y;
		_mdlPos.z += z;

	}

	void MODEL::set_position(float x, float y, float z) {

		_translationMtrx = glm::mat4(1.0f);

		_mdlPos.x = x;
		_mdlPos.y = y;
		_mdlPos.z = z;

	}

	void MODEL::scale(float x, float y, float z) {

		_mdlScale.x += x;
		_mdlScale.y += y;
		_mdlScale.z += z;

	}

	void MODEL::set_scale(float x, float y, float z) {

		_mdlScale.x = x;
		_mdlScale.y = y;
		_mdlScale.z = z;

	}

	void MODEL::rotate(float speed, const glm::vec3& angle) {

		_rotationMtrx = glm::rotate(_rotationMtrx, float(glfwGetTime()) * speed, angle);

	}

	unsigned int MODEL::get_vrtx_count() const { 

		return _totalVertexCount;
	}

	std::string MODEL::get_name() const {

		return _name;
	}

	inline void MODEL::print_model_data() const {

		std::stringstream ss;

		ss << "<|MODEL INFO|>\n"
			<< "\"" << _name << "\"\n"
			<< "Vertex Count [" << _totalVertexCount << "]\n"
			<< "Model Path [" << _modelPath << "]\n";

		std::cout << ss.str() << '\n';

	}

	glm::vec3 MODEL::get_position() const {

		return _mdlPos;
	}

	float MODEL::get_ambient_light_intensity() const {

		return _ambientIntensity;
	}

	float MODEL::get_specularity() const {

		return _specularIntensity;
	}

	glm::vec4 MODEL::get_solid_color() const {

		return _solidColor;
	}

	void MODEL::set_solid_color(glm::vec4 color) {

		_solidColor = color;
	}

	void MODEL::set_ambient_light_intensity(float ambientIntensity) {

		_ambientIntensity = ambientIntensity;
	}

	void MODEL::set_specularity(float specularIntensity) {

		_specularIntensity = specularIntensity;
	}

	void MODEL::set_pixel_mode(unsigned int pixelMode) {

		_pixelMode = pixelMode;
	}

	unsigned int MODEL::get_pixel_mode() const {

		return _pixelMode;
	}

}