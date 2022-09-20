#pragma once

#include <Windows.h>
#include <sstream>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>

#include "../util/exceptions.h"
#include "../util/timer.h"
#include "../util/logger.hpp"
#include "../input/msinput.h"

class MOUSE;

namespace GFXREN {

	class GLCONTEXT {

    public:

        GLCONTEXT() = delete;
        GLCONTEXT(const GLCONTEXT&) = delete;
        GLCONTEXT& operator = (const GLCONTEXT&) = delete;

        // Construct/Setup
        GLCONTEXT(
            const char* wndClassName,
            const char* icoPath,
            bool fullscreenBorderless,
            bool swap = false,
            bool log = true,
            int wndX = 0, int wndY = 0,
            int wndW = 1280, int wndH = 720
        );

        // Start main update loop
        int     run(void(*update)());
        void    terminate();
        
        // Frametime ralted methods
        inline void frametime_calc();
        double      get_deltaTime() const;
        double      get_lastFrameTime() const;
        double      get_currentFrameTime() const;

        // Monitor and resolution related methods
        void enable_full_screen();
        void disable_full_screen();
        void toggle_full_screen();
        bool is_fullscreen() const;

        glm::vec2       get_screen_resolution() const;
        unsigned int    get_screen_width() const;
        unsigned int    get_screen_height() const;

        void enable_face_culling();
        void disable_face_culling();
        void toggle_face_culling();

        // Window decoration
        void set_window_icon(const char* path);
        void set_window_title(const char* title);
        void set_console_title(const char* title);

        // FPS related methods
        inline int  get_fps() const;
        inline int  get_smooth_fps() const;
        void        show_fps_and_mspos(const char* title, const MOUSE& ms);

        // Get GPU and system info
        inline const char*  get_adapter_vendor() const;
        inline const char*  get_adapter_info() const;
        inline const char*  get_gl_version() const;
        inline void         print_system_info() const;

        GLFWwindow* get_window_handle() const;
        HWND        get_console_handle() const;

    private:

        GFXREN::TIMER   _timer;
        bool            _isTerminated;

        // General data
        const char* _wndClassName;
        const char* _icoPath;

        // Window handle
        GLFWwindow* _window;
        HWND        _console;

        // Frame size
        unsigned int _wndX;
        unsigned int _wndY;
        unsigned int _wndW;
        unsigned int _wndH;

        // Monitor and resolution data
        const glm::vec2     _monitorResolution;
        GLFWmonitor*        _monitor;
        const GLFWvidmode*  _videoMode;
        bool                _fullscreenBorderless;
        bool                _fullscreen;
        unsigned int        _refreshRate;

        bool _faceCulling;
        bool _swap;

        // Frametime data
        double _deltaTime;
        double _lastFrame;
        double _currentFrame;

        unsigned int _smoothFPS;
        
        // Main update loop pointer
        void (*_update)();

        // Setup data
        int init();
        int create_window();
        int set_up_and_configure();
        int load_glad() const;

        // Input callbacks
        void            process_input(GLFWwindow* window);
        static void     framebuffer_size_callback(GLFWwindow*, int width, int height);

	};

    int GLCONTEXT::get_fps() const {

        return int(1.0 / _deltaTime);
    }

    int GLCONTEXT::get_smooth_fps() const {

        return _smoothFPS;
    }

}