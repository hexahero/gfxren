#include "glctx.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../global.h"

namespace GFXREN {

    GLCONTEXT::GLCONTEXT(
        const char* wndClassName, 
        const char* icoPath, 
        int wndX, int wndY, int wndW, int wndH, 
        bool log, bool swap
    )
        :
        wndClassName(wndClassName),
        icoPath(icoPath),
        wndX(wndX),
        wndY(wndY),
        wndH(wndH),
        wndW(wndW),
        swap(swap)
    {   

        HWND console = GetConsoleWindow();
        MoveWindow(console, 90, 150, 680, 850, TRUE);
        SetConsoleTitleA("GFXREN LOG");

        if (!log) { ShowWindow(console, SW_HIDE); }

        logger.clog("=======================[GFXREN]=======================", GFXRENCLR);
        logger.clog("GRAPHICS API INITIALIZATION...", LINFO);

        init(log);

        logger.clog("OPENGL API INITIALIZED", LSUCCESS);
        
        create_window();
        set_up_and_configure();
        load_glad();

        std::stringstream ss; 
        ss << "CONTEXT STARTED IN: " << timer.peek_time() << '\n';
        logger.clog(ss.str());
        
    }

    void GLCONTEXT::frametime_calc() {
    
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    
    }

    double GLCONTEXT::get_deltaTime() const { 
        
        return deltaTime; 
    }

    double GLCONTEXT::get_lastFrameTime() const { 
        
        return lastFrame; 
    }

    double GLCONTEXT::get_currentFrameTime() const { 
        
        return currentFrame; 
    }

    void GLCONTEXT::enable_full_screen() {

        glfwSetWindowMonitor(window, true ? glfwGetPrimaryMonitor() : NULL, 0, 0, 1920, 1080, GLFW_DONT_CARE);
    }

    unsigned int GLCONTEXT::get_screen_width() const { 
        
        return wndW; 
    }

    unsigned int GLCONTEXT::get_screen_height() const { 
        
        return wndH; 
    }

    void GLCONTEXT::set_window_icon(const char* path) {

        GLFWimage images[1];

        images[0].pixels = stbi_load(path, &images[0].width, &images[0].height, 0, 4);

        glfwSetWindowIcon(window, 1, images);

        stbi_image_free(images[0].pixels);

    }

    void GLCONTEXT::set_window_title(const char* title) { 
        
        glfwSetWindowTitle(window, title); 
    }

    void GLCONTEXT::set_console_title(const char* title) { 
        
        SetConsoleTitleA(title); 
    }

    int GLCONTEXT::get_fps() const { 
        
        return int(1.0 / deltaTime); 
    }

    void GLCONTEXT::show_fps_and_mspos(const char* title, MOUSE& ms) {

        std::stringstream winTitle;
        winTitle << title << get_fps() << " fps | cursor X:" << ms.get_mouse_x() << " Y:" << ms.get_mouse_y();
        set_window_title(winTitle.str().c_str());

    }

    const char* GLCONTEXT::get_adapter_vendor() const { 
        
        return reinterpret_cast<const char*>(glGetString(GL_VENDOR)); 
    }

    const char* GLCONTEXT::get_adapter_info() const { 
        
        return reinterpret_cast<const char*>(glGetString(GL_RENDERER)); 
    }

    const char* GLCONTEXT::get_gl_version() const { 
        
        return reinterpret_cast<const char*>(glGetString(GL_VERSION)); 
    }

    void GLCONTEXT::print_system_info() const {

        std::stringstream info;

        info
        << "[OpenGL] " << get_gl_version()
        << "\n" << get_adapter_info();

        logger.clog(info.str().c_str());
        logger.clog(get_adapter_vendor(), LSUCCESS);

    }

    GLFWwindow* GLCONTEXT::get_window_handle() const { 
        
        return window; 
    }

    int GLCONTEXT::init(bool log) {

        glfwInit();
        monitor = glfwGetPrimaryMonitor();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#endif

        return 0;
    }

    int GLCONTEXT::create_window() {

        window = glfwCreateWindow(wndW, wndH, wndClassName, NULL, NULL);

        if (window == NULL) {

            EXCEPTION("WINDOW CREATION FAILURE (GLFWwindow == nullptr)", true);
            glfwTerminate();

            return -1;
        }
        else {

            logger.clog("WINDOW CREATED: ", LSUCCESS);
            std::cout << wndClassName << '\n';

        }

        return 0;
    }

    int GLCONTEXT::set_up_and_configure() {

        glfwSetWindowPos(window, wndX, wndY);
        set_window_icon(icoPath);

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSwapInterval(swap);

        return 0;
    }

    int GLCONTEXT::load_glad() {

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

            EXCEPTION("GLAD INITIALIZATION FAILED\n", false);

            return -1;
        }

        print_system_info();

        return 0;
    }

    int GLCONTEXT::run(void(*update)()) {

        //Root update loop
        while (!glfwWindowShouldClose(window)) {

            frametime_calc();
            process_input(window);

            update();

            glfwSwapBuffers(window);
            glfwPollEvents();

        }

        glfwTerminate();

        return 0;
    }

    void GLCONTEXT::process_input(GLFWwindow* window) {

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

            glfwSetWindowShouldClose(window, true);
        }

    }

    void GLCONTEXT::framebuffer_size_callback(GLFWwindow* window, int width, int height) { 
        
        glViewport(0, 0, width, height); 
    }

}