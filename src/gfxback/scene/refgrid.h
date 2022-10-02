#pragma once

#include "../rendering/renderer.h"
#include "../shader/shader.h"
#include "../asset/model/model.h"

namespace GFXREN {

	class REFGRID : public GFXREN::MODEL {

	public:

		REFGRID(const REFGRID&) = delete;
		REFGRID& operator = (const REFGRID&) = delete;

		REFGRID();

		GFXREN::SHADER& get_shader();

	private:

		GFXREN::SHADER	_shader;

		bool _isRefgridShown;

	};

}