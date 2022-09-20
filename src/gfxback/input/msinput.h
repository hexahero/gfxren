#pragma once

#include <queue>
#include <functional>

#include "../context/glctx.h"
#include <glm.hpp>

namespace GFXREN {

	class MOUSE {
	
	public:

		MOUSE() = delete;
		MOUSE(GLFWwindow* window);

		void cursor_update();

		void	on_button_press(unsigned int buttonCode, std::function<void()> funcptr);
		int		press(int buttonCode);
		bool	scroll();

		inline glm::vec2	get_mouse_xy() const;
		inline double		get_mouse_x() const;
		inline double		get_mouse_y() const;
		inline double		get_mouse_dx();
		inline double		get_mouse_dy();
		inline double		get_mouse_lastX() const;
		inline double		get_mouse_lastY() const;
		inline double		get_mouse_scrollDx();
		inline double		get_mouse_scrollDy();

		inline bool hover() const;
		inline void show_cursor();
		inline void hide_cursor();
		inline void toggle_cursor();
		inline void lock_cursor();
		inline bool is_cursor_hidden() const;

		void print_cursor_position();

	private:

		GLFWwindow* _window;

		static std::vector<std::function<void()>>	_actions;
		static std::vector<unsigned int>			_buttons;

		double _x;
		double _y;
		double _dx;
		double _dy;
		double _lastX;
		double _lastY;

		static double _scrollDx;
		static double _scrollDy;

		bool _firstMove;
		bool _cursorHidden;

		static void button_callback(GLFWwindow* window, int, int, int);
		static void wheel_callback(GLFWwindow*, double dx, double dy);

	};

	glm::vec2 MOUSE::get_mouse_xy() const {

		return { _x, _y };
	}

	double MOUSE::get_mouse_x() const { 
		
		return _x; 
	}

	double MOUSE::get_mouse_y() const { 
		
		return _y; 
	}

	double MOUSE::get_mouse_dx() {

		double dx = _dx;
		_dx = 0;

		return dx;
	}

	double MOUSE::get_mouse_dy() {

		double dy = _dy;
		_dy = 0;

		return dy;
	}

	double MOUSE::get_mouse_lastX() const { 
		
		return _lastX; 
	}

	double MOUSE::get_mouse_lastY() const { 
		
		return _lastY; 
	}

	double MOUSE::get_mouse_scrollDx() {

		double scrollDx = _scrollDx;
		_scrollDx = 0;

		return scrollDx;
	}

	double MOUSE::get_mouse_scrollDy() {

		double scrollDy = _scrollDy;
		_scrollDy = 0;

		return scrollDy;
	}

	bool MOUSE::hover() const {

		if (glfwGetWindowAttrib(_window, GLFW_HOVERED)) return true;

		return false;
	}

	void MOUSE::show_cursor() { 
		
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
		_cursorHidden = false;
	
	}

	void MOUSE::hide_cursor() { 
		
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); 
		_cursorHidden = true;

	}

	void MOUSE::lock_cursor() { 
		
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
		_cursorHidden = true;

	}

	void MOUSE::toggle_cursor() {

		if (_cursorHidden == false)
			lock_cursor();
		else
			show_cursor();

	}

	bool MOUSE::is_cursor_hidden() const {

		return _cursorHidden;
	}

}