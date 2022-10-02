#pragma once

#include <map>
#include <functional>
#include <gfxren.h>

#define imgui ImGui
#define action(action) _actions.find(action)->second()

extern float						clearColor[4];
extern bool							refgridOn;
extern bool							lightSourceOn;
extern GFXREN::CAMERA			    camera;
extern GFXREN::LIGHTSOURCE			lightSource;
extern std::vector<GFXREN::MODEL>	models;

namespace {

	// Sizes
	constexpr ImVec2 renderSettingsWindowSizeXY		= { 420.0f, 300.0f };

	constexpr ImVec2 modelsSettingsWindowSizeXY		= { 420.0f, 620.0f };
	constexpr ImVec2 modelsListboxSizeXY			= { 405.0f, 511.0f };
	constexpr ImVec2 addModelButtonSizeXY			= { 110, 20 };

	constexpr ImVec2 sceneSettingsWindowSizeXY		= { 420.0f, 370.0f };
	constexpr ImVec2 applicationSettingsSizeXY		= { 420.0f, 300.0f };

	// Offsets
	constexpr ImVec2 renderSettingsWindowOffsetXY		= { 12, 60 };
	constexpr ImVec2 modelsSettingsWindowOffsetXY		= { 74, 60 };
	constexpr ImVec2 sceneSettingsWindowOffsetXY		= { 136, 60 };
	constexpr ImVec2 applicationSettingsWindowOffsetXY	= { 200, 60 };

}

struct MDLATTRIB {

	float			_scaleFloat = 1.0f;
	glm::fvec3		_translateVec = { 0.0f, 0.0f, 0.0f };
	int				_coloringMode = GFXREN_ILLUMINATED;

	float			_ambientIntensityFloat = 0.5f;
	float			_specularityFloat = 0.5f;
	float			_solidColor[4] = { 0.15f, 0.15f, 0.15f, 1.0f };

};

class DEMOGUI : public GFXREN::GUI {

public:

	// Construct
	DEMOGUI(GFXREN::GLCONTEXT& app);

	// Register actions for GUI elements
	void register_action(const std::string& name, std::function<void()> action);

	// Draw GUI
	void draw();

private:

	// Draw GUI elements
	void draw_title_bar(bool* titleBar);
	void draw_render_settings_window(bool* renderSettingsWindow);
	void draw_models_settings_window(bool* modelsSettingsWindow);
	void draw_model_listbox();
	void draw_scene_settings_window(bool* sceneSettingsWindow);
	void draw_application_settings_window(bool* applicationSettingsWindow);

	// GUI styling and coloring methods
	void push_style_color(const ImGuiCol stylingTarget, const ImVec4& color) const;
	void pop_style_color(const unsigned int popsCount = 1) const;

	// General
	GFXREN::GLCONTEXT&								_app;
	std::map<std::string, std::function<void()>>	_actions;

	// GUI styling and coloring data
	ImGuiStyle& _style;
	ImVec4*		_color;

	// on/off states
	bool _showTitleBar;

	bool _showRenderSettingsWindow;
	bool _showModelsSettingsWindow;
	bool _showSceneSettingsWindow;
	bool _showApplicationSettingsWindow;

	// Model data
	std::vector<MDLATTRIB> _modelAttributes;

};