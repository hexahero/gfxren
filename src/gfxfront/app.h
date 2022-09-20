/*

TODO:

make Exceptions class actually throw exceptions xddd
deal with shader linkage incorrect exception
handle call errors in modules

*/

//#define SHADER_DRAW

#pragma once

#include <iostream>
#include <vector>
#include <gfxren.h>

#include "global.states.h"
#include "gui/demogui.h"

GFXREN::GLCONTEXT app(
    "GFXREN DEMO (OpenGL) ",
    "../resources/ico/cog_small.png",
    FULLSCREEN_BORDERLESS,
    VSYNC_ENABLED,
    LOGGING_ENABLED
);
GFXREN::RENDERER renderer;
GFXREN::MOUSE mouse(app.get_window_handle());

#ifdef SHADER_DRAW

GFXREN::CANVAS canvas(app, mouse);

GFXREN::SHADER sandboxShaderCircle(
    DEFAULT_DIR"minimal.vrtx.glsl",
    DEFAULT_DIR"sandbox/mouse_pos_circle.pxl.glsl"
);
GFXREN::SHADER sandboxShaderRect(
    DEFAULT_DIR"minimal.vrtx.glsl",
    DEFAULT_DIR"sandbox/resizable_rect.pxl.glsl"
);
GFXREN::SHADER shaderNoise(
    DEFAULT_DIR"minimal.vrtx.glsl",
    DEFAULT_DIR"third_party/noise.pxl.glsl"
);
GFXREN::SHADER shaderCubeLines(
    DEFAULT_DIR"minimal.vrtx.glsl",
    DEFAULT_DIR"third_party/cube_lines.pxl.glsl"
);

#else

GFXREN::CAMERA camera(app.get_screen_width(), app.get_screen_height(), { 0.0f, 10.5f, 18.0f });
GFXREN::KEYBOARD keyboard(app.get_window_handle());
GFXREN::LOGGER<const char*> logger;
DEMOGUI gui(app);

GFXREN::SHADER basicShader(
    DEFAULT_DIR"basic.vrtx.glsl",
    DEFAULT_DIR"basic.pxl.glsl"
);

GFXREN::SHADER refgridShader(
    DEFAULT_DIR"scene/refgrid.vrtx.glsl",
    DEFAULT_DIR"scene/refgrid.pxl.glsl"
);

GFXREN::SHADER lightsourceShader(
    DEFAULT_DIR"scene/lightsource.vrtx.glsl",
    DEFAULT_DIR"scene/lightsource.pxl.glsl"
);

GFXREN::MODEL refgrid(
    "Reference grid",
    GFXREN::UTIL::get_relative_path("gfxren") + "resources/models/refgrid/refgrid.gltf",
    { 0.0f, 0.0f, 0.0f }
);

GFXREN::MODEL lightsource(
    "Light source",
    GFXREN::UTIL::get_relative_path("gfxren") + "resources/models/hipoly_sphere/sphere.gltf",
    { 10.0f, 9.0f, 0.0f }
);

#endif

std::vector<GFXREN::MODEL> models;