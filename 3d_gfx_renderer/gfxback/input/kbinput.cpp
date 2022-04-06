#include "kbinput.h"

namespace GFXREN {

	GLFWwindow* KEYBOARD::window;

	std::vector<std::function<void()>> KEYBOARD::actions;
	std::vector<unsigned int> KEYBOARD::keys;

	KEYBOARD::KEYBOARD(GLFWwindow* window) {

		this->window = window;
		glfwSetKeyCallback(window, callback);

	}

	void KEYBOARD::on_key_press(unsigned int keycode, std::function<void()> funcptr) {
		
		keys.push_back(keycode);
		actions.push_back(funcptr);
		
	}

	bool KEYBOARD::press(int keycode) { return glfwGetKey(window, keycode); }

	void KEYBOARD::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

		for (unsigned int i = 0; i != keys.size(); ++i) {

			if (glfwGetKey(window, keys[i]) == GLFW_PRESS) { actions[i](); }
		}

	}

}