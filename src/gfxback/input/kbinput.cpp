#include "kbinput.h"

namespace GFXREN {

	GLFWwindow* KEYBOARD::_window;

	std::vector<std::function<void()>>	KEYBOARD::_actions;
	std::vector<unsigned int>			KEYBOARD::_keys;

	KEYBOARD::KEYBOARD(GLFWwindow* window) {

		_window = window;
		glfwSetKeyCallback(window, callback);

	}

	void KEYBOARD::on_key_press(unsigned int keycode, std::function<void()> funcptr) {
		
		_keys.push_back(keycode);
		_actions.push_back(funcptr);
		
	}

	bool KEYBOARD::press(int keycode) { 
		
		return glfwGetKey(_window, keycode);
	}

	void KEYBOARD::callback(GLFWwindow* window, int, int, int, int) {

		for (unsigned int i = 0; i != _keys.size(); ++i) {

			if (glfwGetKey(window, _keys[i]) == GLFW_PRESS) { _actions[i](); }
		}

	}

}