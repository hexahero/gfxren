#include "msinput.h"

namespace GFXREN {

	std::vector<std::function<void()>> MOUSE::actions;
	std::vector<unsigned int> MOUSE::buttons;

	double MOUSE::scrollDx;
	double MOUSE::scrollDy;

	MOUSE::MOUSE(GLFWwindow* window) {

		this->window = window;
		glfwSetMouseButtonCallback(window, button_callback);
		glfwSetScrollCallback(window, wheel_callback);

		lock_cursor();

	}

	void MOUSE::cursor_update() {

		glfwGetCursorPos(window, &x, &y);

		if (firstMove) {

			lastX = x;
			lastY = y;
			firstMove = false;

		}

		dx = x - lastX;
		dy = lastY - y;
		lastX = x;
		lastY = y;

	}

	void MOUSE::on_button_press(unsigned int buttonCode, std::function<void()> funcptr) {

		buttons.push_back(buttonCode);
		actions.push_back(funcptr);
		
	}

	int MOUSE::press(int buttonCode) { return glfwGetMouseButton(window, buttonCode) == GLFW_PRESS; }

	bool MOUSE::scroll() {

		if (scrollDy != 0 || scrollDx != 0) { return true; }

		return false;
	}

	void MOUSE::print_cursor_position() {
		
		glfwGetCursorPos(window, &x, &y);
		std::cout << "Mouse position: X(" << x << ") Y(" << y << ")" << std::endl; 
	
	}

	void MOUSE::button_callback(GLFWwindow* window, int button, int action, int mods) {

		for (unsigned int i = 0; i != buttons.size(); ++i) {

			if (glfwGetMouseButton(window, buttons[i]) == GLFW_PRESS) { actions[i](); }
		}

	}

	void MOUSE::wheel_callback(GLFWwindow* window, double dx, double dy) {

		scrollDx = dx;
		scrollDy = dy;

	}

}