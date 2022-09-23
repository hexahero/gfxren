#pragma once

constexpr auto FULLSCREEN_BORDERLESS	= true;
constexpr auto VSYNC_ENABLED			= true;
constexpr auto LOGGING_ENABLED			= true;

int		cameraMode		= CAM_TYPE_FLYCAM_MS;
float	clearColor[4]	{ 0.0f, 0.0f, 0.0f, 1.0f };

bool	wireframeMode	= false;
bool	guiEnabled		= true;
bool	refgridOn		= true;
bool	lightSourceOn	= true;