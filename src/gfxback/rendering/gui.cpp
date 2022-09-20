#include "gui.h"

namespace GFXREN {

	GUI::GUI(GLFWwindow* window) {

		imgui_initialize(window);
	}

	void GUI::imgui_initialize(GLFWwindow* window) {

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		_guiIO = &ImGui::GetIO(); 
		reinterpret_cast<void*>(_guiIO);
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

	}

	void GUI::update() {

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

	}

	void GUI::render() {

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void GUI::destroy() {

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

	}

	bool GUI::is_capturing_mouse() const {

		return _guiIO->WantCaptureMouse;
	}

}