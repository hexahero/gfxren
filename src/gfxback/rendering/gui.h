#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include "colors.h"

namespace GFXREN {

	class GUI {

	public:

		GUI() = delete;
		GUI(const GUI&) = delete;

		// Coustruct/setup
		GUI(GLFWwindow* window);
		~GUI();
		void imgui_initialize(GLFWwindow* window);

		// Base behaviour
		void update();
		void render();
		void destroy();

		bool is_capturing_mouse() const;

	protected:

		ImGuiIO* _guiIO;

	};

}