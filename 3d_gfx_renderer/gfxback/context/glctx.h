#pragma once

#include <Windows.h>
#include <sstream>

#include <glad.h>
#include <GLFW/glfw3.h>

#include "../util/exceptions.h"
#include "../util/timer.h"
#include "../util/logger.h"
#include "../input/msinput.h"

class MOUSE;

#define ASSERT(x) if (!(x)) __debugbreak();

#define GL_TRY(x)                               \
gl_clear_err();                                 \
x;                                              \
ASSERT(gl_err_log(#x, __FILE__, __LINE__))      \

namespace GFXREN {

    static void gl_clear_err() { while (glGetError() != GL_NO_ERROR); }

    static void gl_check_err() {

        std::ostringstream msg;

        while (GLenum errmsg = glGetError()) {

            msg << errmsg;
            EXCEPTION(msg.str().c_str(), false)

        }

    }

    static bool gl_err_log(const char* function, const char* file, int line) {

        GFXREN::LOGGER<const char*> logger;

        while (GLenum errmsg = glGetError()) {

            logger.set_text_color(LERROR);

            std::cout << "[GL ERROR] ";

            logger.set_text_color(LINFO);

            std::cout
            << "|" << errmsg << "| "
            << "FILE |" << file << "| " 
            << "LINE |"<< line << "|" 
            << std::endl;

            return false;
        }

        return true;
    }

	class GLCONTEXT {

    public:

        GLCONTEXT() = delete;
        GLCONTEXT& operator = (const GLCONTEXT&) = delete;
        GLCONTEXT(
            const char* wndClassName, 
            const char* icoPath, 
            int wndX, int wndY, int wndW, int wndH, 
            bool log, bool swap
        );

        int run(void(*update)());
        
        inline void frametime_calc();
        double get_deltaTime() const;
        inline double get_lastFrameTime() const;
        inline double get_currentFrameTime() const;

        void enable_full_screen();

        inline unsigned int get_screen_width() const;
        inline unsigned int get_screen_height() const;

        void set_window_icon(const char* path);
        void set_window_title(const char* title);
        void set_console_title(const char* title);

        inline int get_fps() const;
        void show_fps_and_mspos(const char* title, MOUSE& ms);

        inline const char* get_adapter_vendor() const;
        inline const char* get_adapter_info() const;
        inline const char* get_gl_version() const;
        inline void print_system_info() const;

        GLFWwindow* get_window_handle() const;

    private:

        GFXREN::TIMER timer;

        GLFWwindow* window;
        GLFWmonitor* monitor;

        const char* icoPath;
        const char* wndClassName;

        unsigned int wndX = 400;
        unsigned int wndY = 300;
        unsigned int wndW = 800;
        unsigned int wndH = 600;

        double deltaTime = 0.0f;
        double lastFrame = 0.0f;
        double currentFrame = 0.0f;

        bool swap = true;

        void (*update)() = nullptr;

        int init(bool log);
        int create_window();
        int set_up_and_configure();
        int load_glad();

        void process_input(GLFWwindow* window);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	};

}

#define GLERR_CLEAR__ gl_clear_err();
#define __GLERR_CHECK ;gl_check_err();