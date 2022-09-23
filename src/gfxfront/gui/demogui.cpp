#include "demogui.h"

DEMOGUI::DEMOGUI(GFXREN::GLCONTEXT& app)
	:
	GFXREN::GUI(app.get_window_handle()),
	_app(app),
	_style(ImGui::GetStyle()),
	_color(_style.Colors),
	_showTitleBar(true),
	_showRenderSettingsWindow(false),
	_showModelsSettingsWindow(false),
	_showSceneSettingsWindow(false),
	_showApplicationSettingsWindow(false)
{

	// Set up GUI elements' styling
	_style.WindowMenuButtonPosition = ImGuiDir_None;
	_style.FrameRounding = 3.0;

	// Set up GUI elements' coloring
	_color[ImGuiCol_WindowBg]				= { GFXREN_GUI_GREY_WINBG };
	_color[ImGuiCol_TitleBg]				= { GFXREN_GUI_GREY_WINBG };
	_color[ImGuiCol_TitleBgActive]			= { GFXREN_GUI_GREY_WINBG };

	_color[ImGuiCol_Border]					= { GFXREN_BLACK };

	_color[ImGuiCol_Button]					= { GFXREN_GUI_GREY_WINBG };
	_color[ImGuiCol_ButtonHovered]			= { GFXREN_GUI_PURPLE_HOVER };
	_color[ImGuiCol_ButtonActive]			= { GFXREN_GUI_PURPLE_ACTIVE };

	_color[ImGuiCol_FrameBg]				= { GFXREN_GUI_PURPLE_FRAME };
	_color[ImGuiCol_FrameBgHovered]			= { GFXREN_GUI_PURPLE_HOVER };
	_color[ImGuiCol_FrameBgActive]			= { GFXREN_GUI_PURPLE_ACTIVE };
	_color[ImGuiCol_CheckMark]				= { GFXREN_WHITE };

	_color[ImGuiCol_ScrollbarGrab]			= { GFXREN_GUI_PURPLE_ACTIVE };
	_color[ImGuiCol_ScrollbarGrabHovered]	= { GFXREN_GUI_PURPLE_HOVER };
	_color[ImGuiCol_ScrollbarGrabActive]	= { GFXREN_GUI_PURPLE_ACTIVE };

	_color[ImGuiCol_SliderGrab]				= { GFXREN_GUI_PURPLE_HOVER };
	_color[ImGuiCol_SliderGrabActive]		= { GFXREN_GUI_PURPLE_ACTIVE };

	_color[ImGuiCol_HeaderActive]			= { GFXREN_GUI_PURPLE_ACTIVE };
	_color[ImGuiCol_HeaderHovered]			= { GFXREN_GUI_PURPLE_HOVER };

}

void DEMOGUI::register_action(const std::string& name, std::function<void()> action) {

	_actions.try_emplace(name, action);
}

void DEMOGUI::draw() {

	update();

	if (_showTitleBar)					draw_title_bar(&_showTitleBar);
	if (_showRenderSettingsWindow)		draw_render_settings_window(&_showRenderSettingsWindow);
	if (_showModelsSettingsWindow)		draw_models_settings_window(&_showModelsSettingsWindow);
	if (_showSceneSettingsWindow)		draw_scene_settings_window(&_showSceneSettingsWindow);
	if (_showApplicationSettingsWindow)	draw_application_settings_window(&_showApplicationSettingsWindow);

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
		if (imgui::Button("Render", { 55, 20 })) {

			if (_showRenderSettingsWindow) _showRenderSettingsWindow = false;
			else _showRenderSettingsWindow = true;

		}

		imgui::SameLine();
		if (imgui::Button("Models", { 55, 20 })) {

			if (_showModelsSettingsWindow) _showModelsSettingsWindow = false;
			else _showModelsSettingsWindow = true;

		}

		imgui::SameLine();
		if (imgui::Button("Scene", { 55, 20 })) {

			if (_showSceneSettingsWindow) _showSceneSettingsWindow = false;
			else _showSceneSettingsWindow = true;

		}

		imgui::SameLine();
		if (imgui::Button("Settings", { 70, 20 })) {

			if (_showApplicationSettingsWindow) _showApplicationSettingsWindow = false;
			else _showApplicationSettingsWindow = true;

		}

		// FPS monitoring
		imgui::SameLine();
		imgui::Text(("FPS | " + std::to_string(_app.get_smooth_fps())).c_str());

		imgui::End();

	}

	if (!*titleBar) _app.terminate();

}

void DEMOGUI::draw_render_settings_window(bool* renderSettingsWindow) {

	imgui::SetNextWindowPos(renderSettingsWindowOffsetXY, ImGuiCond_Appearing);

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

		imgui::SetWindowSize(renderSettingsWindowSizeXY);

		// Checkbox state bools
		static bool isFaceCullingCheckBoxChecked	= false;
		static bool isWireframeModeCheckBoxChecked	= false;
		static bool isSurfaceNormalsCheckBoxChecked = false;
		static bool isVsyncOffCheckBoxChecked		= false;

		// Checkboxes
		imgui::Checkbox(" Face culling",						&isFaceCullingCheckBoxChecked);
		imgui::Checkbox(" Wireframe mode",						&isWireframeModeCheckBoxChecked);
		imgui::Checkbox(" Surface normals",						&isSurfaceNormalsCheckBoxChecked);
		imgui::Checkbox(" Disable vertical synchronization",	&isVsyncOffCheckBoxChecked);

		// Clear color palette
		imgui::Text("\nRender clear color");
		imgui::ColorEdit4("color", clearColor);

		// Behaviour
		if (isFaceCullingCheckBoxChecked)
			action("enable_face_culling");
		else
			action("disable_face_culling");

		if (isWireframeModeCheckBoxChecked)
			action("enable_wireframe_mode");
		else
			action("disable_wireframe_mode");

		if (isSurfaceNormalsCheckBoxChecked)
			action("enable_surface_normals");
		else
			action("disable_surface_normals");

		if (isVsyncOffCheckBoxChecked)
			_app.disable_vsync();
		else
			_app.enable_vsync();

		imgui::End();

	}

}

void DEMOGUI::draw_models_settings_window(bool* modelsSettingsWindow) {

	// Temporary styling
	push_style_color(ImGuiCol_Button, { GFXREN_PURPLE_NONNORM });
	push_style_color(ImGuiCol_FrameBg, { GFXREN_DARK_GREY_NONNORM });

	imgui::SetNextWindowPos(modelsSettingsWindowOffsetXY, ImGuiCond_Appearing);

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

		imgui::SetWindowSize(modelsSettingsWindowSizeXY);

		imgui::Text(" Model list");

		// Draw list of model control nodes
		draw_model_listbox();

		// Add model button
		if (imgui::Button("Import model", addModelButtonSizeXY)) {

			std::string filePath = GFXREN::UTIL::get_file_via_dialog(_app.get_window_handle());

			if (filePath != GFXREN_INVALID_FILE_PATH) {

				// Acquire file name and path
				filePath = GFXREN::UTIL::normalize_file_path(filePath);
				std::string fileName = GFXREN::UTIL::get_file_name(filePath);

				// Add new model
				models.emplace_back(GFXREN::MODEL{
					fileName,
					filePath,
					{ 0.0f, 0.0f, 0.0f }
				});

				_modelAttributes.emplace_back(MDLATTRIB());

			}

		}
		
		std::string totalModels = "\nTotal models: " + std::to_string(models.size());
		imgui::Text(totalModels.c_str());

		imgui::End();

	}

	// Pop out temporary styling
	pop_style_color(2);

}

void DEMOGUI::draw_model_listbox() {

	// Create list of added models
	if (imgui::ListBoxHeader("##Models", { modelsListboxSizeXY })) {

		std::vector<unsigned int> nodesToErase;
		unsigned int ctr = 0;

		for (auto& model : models) {

			std::string itemName = model.get_name();

			// Push an unique id so that model attributes might work correctly
			imgui::PushID((itemName + std::to_string(ctr)).c_str());
			push_style_color(ImGuiCol_Header, { GFXREN_GREY_NONNORM });

			if (ImGui::CollapsingHeader(itemName.c_str())) {
				
				imgui::Text(" \nSCALE");

				// Create InputFloat field for scaling
				imgui::PushItemWidth(100.0f);
				imgui::InputFloat("##scale", &_modelAttributes[ctr]._scaleFloat, 0.02f, 1.0f, "%.3f");
				imgui::PopItemWidth();

				imgui::SameLine();
				if (imgui::Button("Set scale")) {

					model.set_scale(
						_modelAttributes[ctr]._scaleFloat,
						_modelAttributes[ctr]._scaleFloat,
						_modelAttributes[ctr]._scaleFloat
					);

				}

				imgui::SameLine();
				if (imgui::Button("Increase scale")) {

					model.scale(
						_modelAttributes[ctr]._scaleFloat,
						_modelAttributes[ctr]._scaleFloat,
						_modelAttributes[ctr]._scaleFloat
					);

				}

				imgui::SameLine();
				if (imgui::Button("Decrease scale")) {

					model.scale(
						-_modelAttributes[ctr]._scaleFloat,
						-_modelAttributes[ctr]._scaleFloat,
						-_modelAttributes[ctr]._scaleFloat
					);

				}

				imgui::Text(" \nPOSITION");

				// Create InputFloat fields for translating
				imgui::PushItemWidth(100.0f);
				imgui::InputFloat(" X axis", &_modelAttributes[ctr]._translateVec.x, 0.5f, INFINITY, "%.3f");
				imgui::PopItemWidth();

				imgui::PushItemWidth(100.0f);
				imgui::InputFloat(" Y axis", &_modelAttributes[ctr]._translateVec.y, 0.5f, INFINITY, "%.3f");
				imgui::PopItemWidth();

				imgui::PushItemWidth(100.0f);
				imgui::InputFloat(" Z axis", &_modelAttributes[ctr]._translateVec.z, 0.5f, INFINITY, "%.3f");
				imgui::PopItemWidth();

				// Translate model
				models[ctr].set_position(
					_modelAttributes[ctr]._translateVec.x,
					_modelAttributes[ctr]._translateVec.y,
					_modelAttributes[ctr]._translateVec.z
				);

				
				// Material setting
				imgui::Text(" \nMATERIAL AND LIGHTING");

				ImGui::PushID("sliders temp styling");
				push_style_color(ImGuiCol_FrameBg, { GFXREN_BLACK_NONNORM });

				ImGui::SliderFloat("ambient light", &_modelAttributes[ctr]._ambientIntensityFloat, -1.5f, 3.0f);
				ImGui::SliderFloat("specularity",	&_modelAttributes[ctr]._specularityFloat, 0.0f, 110.0f);

				pop_style_color();
				ImGui::PopID();

				model.set_ambient_light_intensity(_modelAttributes[ctr]._ambientIntensityFloat);
				model.set_specularity(_modelAttributes[ctr]._specularityFloat);

				// Set pixel mode radio buttons
				imgui::Text(" \nCOLORING MODE");

				ImGui::PushID(&_modelAttributes[ctr]._coloringMode);
				push_style_color(ImGuiCol_FrameBg, { GFXREN_PURPLE_NONNORM });

				ImGui::RadioButton("Illuminated",		&_modelAttributes[ctr]._coloringMode, 4);
				ImGui::RadioButton("Texture only",		&_modelAttributes[ctr]._coloringMode, 3);
				ImGui::RadioButton("Surface normals",	&_modelAttributes[ctr]._coloringMode, 2);
				ImGui::RadioButton("Solid color",		&_modelAttributes[ctr]._coloringMode, 1);

				pop_style_color();
				ImGui::PopID();

				switch (_modelAttributes[ctr]._coloringMode) {

				case GFXREN_SOLID_COLOR:
					models[ctr].set_pixel_mode(GFXREN_SOLID_COLOR);
					break;

				case GFXREN_SURFACE_NORMALS:
					models[ctr].set_pixel_mode(GFXREN_SURFACE_NORMALS);
					break;

				case GFXREN_TEXTURE_ONLY:
					models[ctr].set_pixel_mode(GFXREN_TEXTURE_ONLY);
					break;

				case GFXREN_ILLUMINATED:
					models[ctr].set_pixel_mode(GFXREN_ILLUMINATED);
					break;

				}

				imgui::Text(" ");

			}

			const char* hiddenOrShownButtonLabel;

			if (model.is_hidden())
				hiddenOrShownButtonLabel = "  Show  ";
			else
				hiddenOrShownButtonLabel = "  Hide  ";

			// Hide model button
			if (imgui::Button(hiddenOrShownButtonLabel, { 110, 18 })) {
				
				if (model.is_hidden())
					model.show();
				else
					model.hide();
			
			}

			// Remove model button
			imgui::SameLine();
			if (imgui::Button("  Delete  ", { 110, 18 }))
				nodesToErase.push_back(ctr);

			pop_style_color();
			imgui::PopID();

			++ctr;

		}

		// Erase removed models and their gui list nodes
		for (const auto& nodeToEraseIndex : nodesToErase) {

			models.erase(models.begin() + nodeToEraseIndex);
			_modelAttributes.erase(_modelAttributes.begin() + nodeToEraseIndex);

		}

		imgui::ListBoxFooter();

	}

}

void DEMOGUI::draw_scene_settings_window(bool* sceneSettingsWindow) {

	imgui::SetNextWindowPos(sceneSettingsWindowOffsetXY, ImGuiCond_Appearing);

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

		static float lightingColor[4]{ GFXREN_WHITE };

		imgui::SetWindowSize(sceneSettingsWindowSizeXY);

		// Checkbox state bools
		static bool isHideRefGridCheckBoxChecked		= false;
		static bool isHideLightSourceCheckBoxChecked	= false;
		static bool isDisabeLightingCheckBoxChecked		= false;

		// Checkboxes
		imgui::Checkbox(" Hide reference grid",			&isHideRefGridCheckBoxChecked);
		imgui::Checkbox(" Hide light source sphere",	&isHideLightSourceCheckBoxChecked);
		imgui::Checkbox(" Disable lighting",			&isDisabeLightingCheckBoxChecked);

		// Lighting color palette
		imgui::Text("\nLighting color");
		imgui::ColorEdit4("color", lightingColor);

		lightSource.set_light_color({ lightingColor[0], lightingColor[1], lightingColor[2], lightingColor[3] });

		// Behaviour
		if (isHideRefGridCheckBoxChecked)
			refgridOn = false;
		else
			refgridOn = true;

		if (isHideLightSourceCheckBoxChecked)
			lightSourceOn = false;
		else
			lightSourceOn = true;

		if (isDisabeLightingCheckBoxChecked) {

			lightSource.disable_lighting();

			for (auto& model : models)
				model.set_pixel_mode(GFXREN_TEXTURE_ONLY);

			for (auto& attrib : _modelAttributes)
				attrib._coloringMode = GFXREN_TEXTURE_ONLY;

		}
		else {

			lightSource.enable_lighting();
		}
			
		imgui::End();

	}

}

void DEMOGUI::draw_application_settings_window(bool* applicationSettingsWindow) {

	imgui::SetNextWindowPos(applicationSettingsWindowOffsetXY, ImGuiCond_Appearing);

	// Draw window
	if (!imgui::Begin(
		"Settings",
		applicationSettingsWindow,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings
	)) {

		imgui::End();
	}
	else {

		static bool isEnableImGuiDemoWindowCheckBoxChecked = false;

		imgui::SetWindowSize(applicationSettingsSizeXY);

		imgui::Checkbox(" Open ImGui demo window", &isEnableImGuiDemoWindowCheckBoxChecked);

		if (isEnableImGuiDemoWindowCheckBoxChecked) imgui::ShowDemoWindow();

		imgui::Text((
			"\nSYSTEM INFO:\n" + _app.get_system_info()
		).c_str());

		imgui::End();

	}

}

void DEMOGUI::push_style_color(const ImGuiCol stylingTarget, const ImVec4& color) const {

	const auto& frameBgColor = color;

	imgui::PushStyleColor(
		stylingTarget,
		IM_COL32(
			frameBgColor.x,
			frameBgColor.y,
			frameBgColor.z,
			frameBgColor.w
		)
	);

}

void DEMOGUI::pop_style_color(const unsigned int popsCount) const {

	imgui::PopStyleColor(popsCount);
}