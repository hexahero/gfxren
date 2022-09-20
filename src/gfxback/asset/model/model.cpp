#include "model.h"

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
		_mdlAngle({ 0.0f, 0.0f, 0.0f })
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
		MODELBASE(std::move(model))
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

			GFXREN::MODELBASE::operator = (std::move(model));

			reset_transform_matrices();
			model.~MODEL();

		}

		return *this;
	}

	void MODEL::update(const GFXREN::SHADER& shader) {

		_translateMtrx = glm::translate(_translateMtrx, _mdlPos);
		_scaleMtrx = glm::scale(_scaleMtrx, _mdlScale);
		_modelTransformMtrx = _translateMtrx * _rotationMtrx * _scaleMtrx;

		shader.set_mat4("model", _modelTransformMtrx);

		reset_transform_matrices();

	}

	void MODEL::reset_transform_matrices() {
		
		_modelTransformMtrx	=
		_translateMtrx		=
		_scaleMtrx			=
		_rotationMtrx		= glm::mat4(1.0f);

	}

	void MODEL::enable_textures(const GFXREN::SHADER& shader) {

		shader.use();
		shader.set_bool("isTextured", true);

	}

	void MODEL::disable_textures(const GFXREN::SHADER& shader) {

		shader.use();
		shader.set_bool("isTextured", false);

	}

	void MODEL::move(float x, float y, float z) {

		_mdlPos.x += x;
		_mdlPos.y += y;
		_mdlPos.z += z;

	}

	void MODEL::set_position(float x, float y, float z) {

		_translateMtrx = glm::mat4(1.0f);

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

}