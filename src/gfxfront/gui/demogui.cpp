#include "demogui.h"

DEMOGUI::DEMOGUI(GFXREN::GLCONTEXT& app)
	:
	GFXREN::GUI(app.get_window_handle()),
	_app(app),
	_style(ImGui::GetStyle()),
	_colour(_style.Colors),
	_renderWindowOffsetXY{ 12, 60 },
	_modelsWindowOffsetXY{ 69, 60 },
	_sceneWindowOffsetXY{ 131, 60 },
	_showTitleBar(true),
	_showRenderSettingsWindow(false),
	_showModelsSettingsWindow(false),
	_showSceneSettingsWindow(false)
{

	// Set up GUI elements' styling
	_style.WindowMenuButtonPosition = ImGuiDir_None;
	_style.FrameRounding = 3.0;

	// Set up GUI elements' colouring
	_colour[ImGuiCol_WindowBg]			= { GFXREN_BLACK };
	_colour[ImGuiCol_TitleBg]			= { GFXREN_BLACK };
	_colour[ImGuiCol_TitleBgActive]		= { GFXREN_BLACK };

	_colour[ImGuiCol_Button]			= { GFXREN_BLACK };
	_colour[ImGuiCol_ButtonHovered]		= { GFXREN_GUI_PURPLE_HOVER };
	_colour[ImGuiCol_ButtonActive]		= { GFXREN_GUI_PURPLE_ACTIVE };

	_colour[ImGuiCol_FrameBg]			= { GFXREN_GUI_PURPLE_FRAME };
	_colour[ImGuiCol_FrameBgHovered]	= { GFXREN_GUI_PURPLE_HOVER };
	_colour[ImGuiCol_FrameBgActive]		= { GFXREN_GUI_PURPLE_ACTIVE };
	_colour[ImGuiCol_CheckMark]			= { GFXREN_WHITE };

	_colour[ImGuiCol_HeaderActive]		= { GFXREN_GUI_PURPLE_ACTIVE };
	_colour[ImGuiCol_HeaderHovered]		= { GFXREN_GUI_PURPLE_HOVER };

}

void DEMOGUI::register_action(const std::string& name, std::function<void()> action) {

	_actions.try_emplace(name, action);
}

void DEMOGUI::draw() {

	update();

	if (_showTitleBar)				draw_title_bar(&_showTitleBar);
	if (_showRenderSettingsWindow)	draw_render_settings_window(&_showRenderSettingsWindow);
	if (_showModelsSettingsWindow)	draw_models_settings_window(&_showModelsSettingsWindow);
	if (_showSceneSettingsWindow)	draw_scene_settings_window(&_showSceneSettingsWindow);

	render();

}

void DEMOGUI::draw_title_bar(bool* titleBar) {

	// Draw window
	if (!imgui::Begin(
		" GFXREN DEMO (OpenGL)",
		titleBar,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoSavedSettings
	)) {

		imgui::End();
	}
	else {

		// Acquire frambuffer size
		glm::ivec2 framebuffSize = { 0.0f , 0.0f };
		glfwGetFramebufferSize(_app.get_window_handle(), &framebuffSize.x, &framebuffSize.y);

		// Resize title bar according to framebuffer width
		imgui::SetWindowPos({ -1.0f, -1.0f });
		imgui::SetWindowSize({ static_cast<float>(framebuffSize.x) + 2.0f, 55.0f });

		// Title bar "menu" buttons 
		if (imgui::Button("Render", { 50, 20 })) {

			if (_showRenderSettingsWindow) _showRenderSettingsWindow = false;
			else _showRenderSettingsWindow = true;

		}

		imgui::SameLine();
		if (imgui::Button("Models", { 50, 20 })) {

			if (_showModelsSettingsWindow) _showModelsSettingsWindow = false;
			else _showModelsSettingsWindow = true;

		}

		imgui::SameLine();
		if (imgui::Button("Scene", { 50, 20 })) {

			if (_showSceneSettingsWindow) _showSceneSettingsWindow = false;
			else _showSceneSettingsWindow = true;

		}

		// FPS monitoring
		imgui::SameLine();
		imgui::Text(("FPS | " + std::to_string(_app.get_smooth_fps())).c_str());

		imgui::End();

	}

	if (!*titleBar) _app.terminate();

}

void DEMOGUI::draw_render_settings_window(bool* renderSettingsWindow) {

	imgui::SetNextWindowPos(_renderWindowOffsetXY, ImGuiCond_Appearing);

	// Draw window
	if (!imgui::Begin(
		"Render settings",
		renderSettingsWindow,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings
	)) {

		imgui::End();
	}
	else {

		imgui::SetWindowSize({ 500.0f , 300.0f });

		// Checkbox state bools
		static bool isFaceCullingCheckBoxChecked = false;
		static bool isWireframeModeCheckBoxChecked = false;
		static bool isTexturelessCheckBoxChecked = false;

		// Checkboxes
		imgui::Checkbox(" Face culling", &isFaceCullingCheckBoxChecked);
		imgui::Checkbox(" Wireframe mode", &isWireframeModeCheckBoxChecked);
		imgui::Checkbox(" Textureless", &isTexturelessCheckBoxChecked);

		imgui::Text("\nRender clear colour");
		imgui::ColorEdit4("colour", clearColour);

		// Behaviour
		if (isFaceCullingCheckBoxChecked)
			action("enable_face_culling");
		else
			action("disable_face_culling");

		if (isWireframeModeCheckBoxChecked)
			action("enable_wireframe_mode");
		else
			action("disable_wireframe_mode");

		if (!isTexturelessCheckBoxChecked)
			action("enable_textures");
		else
			action("disable_textures");

		imgui::End();

	}

}

void DEMOGUI::draw_models_settings_window(bool* modelsSettingsWindow) {

	// Temporary styling
	ImVec4 buttonColour = { GFXREN_PURPLE_NONNORM };
	ImVec4 frameBgColour = { GFXREN_DARK_GREY_NONNORM };

	imgui::PushStyleColor(
		ImGuiCol_Button, 
		IM_COL32(
			buttonColour.x, 
			buttonColour.y, 
			buttonColour.z, 
			buttonColour.w
		)
	);
	imgui::PushStyleColor(
		ImGuiCol_FrameBg, 
		IM_COL32(
			frameBgColour.x, 
			frameBgColour.y, 
			frameBgColour.z, 
			frameBgColour.w
		)
	);

	imgui::SetNextWindowPos(_modelsWindowOffsetXY, ImGuiCond_Appearing);

	// Draw window
	if (!imgui::Begin(
		"Model settings",
		modelsSettingsWindow,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings
	)) {

		imgui::End();
	}
	else {

		imgui::SetWindowSize({ 500.0f , 320.0f });

		imgui::Text(" Model list");

		// Draw list of model control nodes
		draw_model_listbox();

		// Add model button
		if (imgui::Button("Add model", { 70, 20 })) {

			std::string filePath = GFXREN::UTIL::get_file_via_dialog(_app.get_window_handle());

			if (filePath != GFXREN_INVALID_FILE_PATH) {

				// Acquire file path and name 
				filePath = GFXREN::UTIL::normalize_file_path(filePath);
				std::string fileName = GFXREN::UTIL::get_file_name(filePath);

				// Add new model
				models.emplace_back(GFXREN::MODEL{
					fileName,
					filePath,
					{ 0.0f, 0.0f, 0.0f }
				});

				// Add GUI-model associated data
				_modelScaleFloats.push_back({ 1.0f });
				_modelTranslateFloats.push_back({ 0.0f, 0.0f, 0.0f });

			}

		}
		
		std::string totalModels = "\nTotal models: " + std::to_string(models.size());
		imgui::Text(totalModels.c_str());

		imgui::End();

	}

	// Pop out temporary styling
	imgui::PopStyleColor();
	imgui::PopStyleColor();

}

void DEMOGUI::draw_model_listbox() {

	// Create list of added models
	if (imgui::ListBoxHeader("##Models", { 485.0f, 211.0f })) {

		std::vector<unsigned int> nodesToErase;
		unsigned int ctr = 0;

		for (auto& model : models) {

			std::string itemName = "model." + model.get_name();

			// Push an unique id so that InputFloat might work correctly
			imgui::PushID((itemName + std::to_string(reinterpret_cast<long long int>(&model))).c_str());

			// Create model node
			if (imgui::TreeNode(itemName.c_str())) {

				imgui::Text(" SCALE");

				// Create InputFloat field for scaling
				imgui::PushItemWidth(100.0f);
				imgui::InputFloat("##scale", &_modelScaleFloats[ctr], 0.02f, 1.0f, "%.3f");
				imgui::PopItemWidth();

				imgui::SameLine();
				if (imgui::Button("Set scale")) {

					model.set_scale(_modelScaleFloats[ctr], _modelScaleFloats[ctr], _modelScaleFloats[ctr]);
				}

				imgui::SameLine();
				if (imgui::Button("Increase scale")) {

					model.scale(_modelScaleFloats[ctr], _modelScaleFloats[ctr], _modelScaleFloats[ctr]);
				}

				imgui::SameLine();
				if (imgui::Button("Decrease scale")) {

					model.scale(-_modelScaleFloats[ctr], -_modelScaleFloats[ctr], -_modelScaleFloats[ctr]);
				}

				imgui::Text(" POSITION");

				// Create InputFloat fields for translating
				imgui::PushItemWidth(100.0f);
				imgui::InputFloat(" X axis", &_modelTranslateFloats[ctr].x, 0.5f, INFINITY, "%.3f");
				imgui::PopItemWidth();
				 
				imgui::PushItemWidth(100.0f);
				imgui::InputFloat(" Y axis", &_modelTranslateFloats[ctr].y, 0.5f, INFINITY, "%.3f");
				imgui::PopItemWidth();

				imgui::PushItemWidth(100.0f);
				imgui::InputFloat(" Z axis", &_modelTranslateFloats[ctr].z, 0.5f, INFINITY, "%.3f");
				imgui::PopItemWidth();

				// Translate model
				models[ctr].set_position(_modelTranslateFloats[ctr].x, _modelTranslateFloats[ctr].y, _modelTranslateFloats[ctr].z);

				// Remove button
				if (imgui::Button("Remove"))
					nodesToErase.push_back(ctr);

				++ctr;

				imgui::TreePop();

			}

			imgui::PopID();

		}

		// Erase removed models and their gui list nodes
		for (const auto& nodeIndex : nodesToErase) {

			models.erase(models.begin() + nodeIndex);
			_modelScaleFloats.erase(_modelScaleFloats.begin() + nodeIndex);
			_modelTranslateFloats.erase(_modelTranslateFloats.begin() + nodeIndex);

		}

		imgui::ListBoxFooter();

	}

}

void DEMOGUI::draw_scene_settings_window(bool* sceneSettingsWindow) {

	imgui::SetNextWindowPos(_sceneWindowOffsetXY, ImGuiCond_Appearing);

	// Draw window
	if (!imgui::Begin(
		"Scene settings",
		sceneSettingsWindow,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings
	)) {

		imgui::End();
	}
	else {

		imgui::SetWindowSize({ 500.0f , 300.0f });
		
		// Checkbox state bools
		static bool isHideRefGridCheckBoxChecked = false;
		static bool isTurnOffLightSourceCheckBoxChecked = false;

		// Checkboxes
		imgui::Checkbox(" Hide reference grid", &isHideRefGridCheckBoxChecked);
		imgui::Checkbox(" Turn off light source", &isTurnOffLightSourceCheckBoxChecked);

		// Behaviour
		if (isHideRefGridCheckBoxChecked)
			refgridOn = false;
		else
			refgridOn = true;

		imgui::End();

	}

}