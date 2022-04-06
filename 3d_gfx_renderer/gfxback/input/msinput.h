#pragma once

#include <queue>
#include <functional>
#include "../context/glctx.h"

namespace GFXREN {

	class MOUSE {
	
	public:

		MOUSE() = delete;
		MOUSE(GLFWwindow* window);

		void cursor_update();

		void on_button_press(unsigned int buttonCode, std::function<void()> funcptr);
		int press(int buttonCode);
		bool scroll();

		inline double get_mouse_x() const;
		inline double get_mouse_y() const;
		inline double get_mouse_dx();
		inline double get_mouse_dy();
		inline double get_mouse_lastX() const;
		inline double get_mouse_lastY() const;
		inline double get_mouse_scrollDx();
		inline double get_mouse_scrollDy();

		inline bool hover() const;
		inline void toggle_cursor();
		inline void show_cursor() const;
		inline void hide_cursor() const;
		inline void lock_cursor() const;

		void print_cursor_position();

	private:

		GLFWwindow* window;

		static std::vector<std::function<void()>> actions;
		static std::vector<unsigned int> buttons;

		double x = 0;
		double y = 0;
		double dx = 0;
		double dy = 0;
		double lastX = 0;
		double lastY = 0;

		static double scrollDx;
		static double scrollDy;

		bool firstMove = true;
		bool cursorHidden = false;

		static void button_callback(GLFWwindow* window, int button, int action, int mods);
		static void wheel_callback(GLFWwindow* window, double dx, double dy);

	};

	double MOUSE::get_mouse_x() const { return x; }

	double MOUSE::get_mouse_y() const { return y; }

	double MOUSE::get_mouse_dx() {

		double _dx = dx;
		dx = 0;

		return _dx;
	}

	double MOUSE::get_mouse_dy() {

		double _dy = dy;
		dy = 0;

		return _dy;
	}

	double MOUSE::get_mouse_lastX() const { return lastX; }

	double MOUSE::get_mouse_lastY() const { return lastY; }

	double MOUSE::get_mouse_scrollDx() {

		double _scrollDx = scrollDx;
		scrollDx = 0;

		return _scrollDx;
	}

	double MOUSE::get_mouse_scrollDy() {

		double _scrollDy = scrollDy;
		scrollDy = 0;

		return _scrollDy;
	}

	bool MOUSE::hover() const {

		if (glfwGetWindowAttrib(window, GLFW_HOVERED)) { return true; }

		return false;
	}

	void MOUSE::toggle_cursor() {

		if (cursorHidden == false) {

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			cursorHidden = true;

		}
		else {

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			cursorHidden = false;

		}

	}

	void MOUSE::show_cursor() const { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

	void MOUSE::hide_cursor() const { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }

	void MOUSE::lock_cursor() const { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }

}