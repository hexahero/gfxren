#include "refgrid.h"

namespace GFXREN {

	REFGRID::REFGRID()
		:
		GFXREN::MODEL(
			"Reference grid",
			GFXREN::UTIL::get_relative_path("gfxren") + "resources/models/refgrid/refgrid.gltf",
			{ 0.0f, 0.0f, 0.0f }
		),
		_shader(
			DEFAULT_DIR"scene/refgrid.vrtx.glsl",
			DEFAULT_DIR"scene/refgrid.pxl.glsl"
		),
		_isRefgridShown(true)
	{

		set_scale(10.0f, 10.0f, 10.0f);
	}

	GFXREN::SHADER& REFGRID::get_shader() {

		return _shader;
	}

}