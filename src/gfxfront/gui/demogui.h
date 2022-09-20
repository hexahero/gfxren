#pragma once

#include <map>
#include <functional>

#include <gfxren.h>

#define imgui ImGui
#define action(action) _actions.find(action)->second()

extern float						clearColour[4];
extern bool							refgridOn;
extern std::vector<GFXREN::MODEL>	models;

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

	// General
	GFXREN::GLCONTEXT&								_app;
	std::map<std::string, std::function<void()>>	_actions;

	// GUI styling and colouring
	ImGuiStyle& _style;
	ImVec4*		_colour;

	// Window offsets
	ImVec2 _renderWindowOffsetXY;
	ImVec2 _modelsWindowOffsetXY;
	ImVec2 _sceneWindowOffsetXY;

	// on/off states
	bool _showTitleBar;

	bool _showRenderSettingsWindow;
	bool _showModelsSettingsWindow;
	bool _showSceneSettingsWindow;

	// Model data
	std::vector<float>		_modelScaleFloats;
	std::vector<glm::fvec3> _modelTranslateFloats;

};