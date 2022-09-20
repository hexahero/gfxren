#include "msinput.h"

namespace GFXREN {

	std::vector<std::function<void()>> MOUSE::_actions;
	std::vector<unsigned int> MOUSE::_buttons;

	double MOUSE::_scrollDx;
	double MOUSE::_scrollDy;

	MOUSE::MOUSE(GLFWwindow* window) 
		:
		_x{ 0 },
		_y{ 0 },
		_dx{ 0 },
		_dy{ 0 },
		_lastX{ 0 },
		_lastY{ 0 },
		_firstMove(true),
		_cursorHidden(false)
	{

		_window = window;

		glfwSetMouseButtonCallback(window, button_callback);
		glfwSetScrollCallback(window, wheel_callback);

		show_cursor();

	}

	void MOUSE::cursor_update() {

		glfwGetCursorPos(_window, &_x, &_y);

		if (_firstMove) {

			_lastX = _x;
			_lastY = _y;
			_firstMove = false;

		}

		_dx = _x - _lastX;
		_dy = _lastY - _y;
		_lastX = _x;
		_lastY = _y;

	}

	void MOUSE::on_button_press(unsigned int buttonCode, std::function<void()> funcptr) {

		_buttons.push_back(buttonCode);
		_actions.push_back(funcptr);
		
	}

	int MOUSE::press(int buttonCode) { 
		
		return glfwGetMouseButton(_window, buttonCode) == GLFW_PRESS; 
	}

	bool MOUSE::scroll() {

		if (_scrollDy != 0 || _scrollDx != 0) return true;

		return false;
	}

	void MOUSE::print_cursor_position() {
		
		glfwGetCursorPos(_window, &_x, &_y);
		std::cout << "Mouse position: X(" << _x << ") Y(" << _y << ")" << std::endl;
	
	}

	void MOUSE::button_callback(GLFWwindow* window, int, int, int) {

		for (unsigned int i = 0; i != _buttons.size(); ++i) {

			if (glfwGetMouseButton(window, _buttons[i]) == GLFW_PRESS) _actions[i]();
		}

	}

	void MOUSE::wheel_callback(GLFWwindow*, double dx, double dy) {

		_scrollDx = dx;
		_scrollDy = dy;

	}

}