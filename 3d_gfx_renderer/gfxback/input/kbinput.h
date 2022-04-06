#pragma once

#include <queue>
#include <bitset>
#include <vector>
#include <functional>

#include "../context/glctx.h"
#include "keycodes.h"

namespace GFXREN {

	class KEYBOARD {

	public:

		KEYBOARD() = delete;
		KEYBOARD(GLFWwindow* window);

		static void on_key_press(unsigned int keycode, std::function<void()> funcptr);
		static bool press(int keycode);
		
	private:

		static GLFWwindow* window;

		static std::vector<std::function<void()>> actions;
		static std::vector<unsigned int> keys;

		static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	};

}