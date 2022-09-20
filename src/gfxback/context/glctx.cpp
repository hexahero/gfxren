#include "glctx.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#ifdef PROFILE
#include <Tracy.hpp>
#include <TracyOpenGL.hpp>
#endif

#include "../global.h"

namespace GFXREN {

    GLCONTEXT::GLCONTEXT(
        const char* wndClassName,
        const char* icoPath,
        bool fullscreenBorderless,
        bool swap, 
        bool log,
        int wndX, int wndY, 
        int wndW, int wndH
    )
        :
        _isTerminated(false),
        _wndClassName(wndClassName),
        _icoPath(icoPath),
        _wndX(wndX),
        _wndY(wndY),
        _wndW(wndW),
        _wndH(wndH),
        _monitorResolution({ 
            GetSystemMetrics(SM_CXSCREEN), 
            GetSystemMetrics(SM_CYSCREEN) 
        }),
        _fullscreenBorderless(fullscreenBorderless),
        _fullscreen(false),
        _faceCulling(false),
        _swap(swap),
        _deltaTime{ 0.0f },
        _lastFrame{ 0.0f },
        _currentFrame{ 0.0f },
        _smoothFPS{ 0 },
        _update(nullptr)
    {   

        // Set resolution in accordance to the chosen window mode
        if (fullscreenBorderless) {

            this->_wndW = static_cast<unsigned int>(_monitorResolution.x);
            this->_wndH = static_cast<unsigned int>(_monitorResolution.y);
            this->_wndX = 0;
            this->_wndY = 0;

        }
        else {
            
            this->_wndW = wndW;
            this->_wndH = wndH;
            this->_wndX = 0;
            this->_wndY = 60;

        }

        _console = GetConsoleWindow();
        MoveWindow(_console, 90, 150, 680, 850, TRUE);
        SetConsoleTitleA("GFXREN LOG");

        if (!log) { ShowWindow(_console, SW_HIDE); }

        logger.clog("=======================[GFXREN]=======================", GFXRENCLR);
        logger.clog("GRAPHICS API INITIALIZATION...", LINFO);

        init();

        logger.clog("OPENGL API INITIALIZED", LSUCCESS);
        
        create_window();
        set_up_and_configure();
        load_glad();
        
        std::stringstream ss; 
        ss << "CONTEXT STARTED IN: " << _timer.peek_time() << '\n';
        logger.clog(ss.str());

        #ifdef PROFILE
            TracyGpuContext;
        #endif
        
    }

    void GLCONTEXT::frametime_calc() {
    
        _currentFrame = glfwGetTime();
        _deltaTime = _currentFrame - _lastFrame;
        _lastFrame = _currentFrame;
    
    }

    double GLCONTEXT::get_deltaTime() const { 
        
        return _deltaTime; 
    }

    double GLCONTEXT::get_lastFrameTime() const { 
        
        return _lastFrame; 
    }

    double GLCONTEXT::get_currentFrameTime() const { 
        
        return _currentFrame; 
    }

    void GLCONTEXT::enable_full_screen() {

        _fullscreen = true;
        glfwSetWindowMonitor(_window, true ? glfwGetPrimaryMonitor() : NULL, 0, 0, 1920, 1080, _videoMode->refreshRate);

    }

    void GLCONTEXT::disable_full_screen() {
    
        _fullscreen = false;
        glfwSetWindowMonitor(_window, NULL, 0, 0, 1920, 1080, _videoMode->refreshRate);

    }

    void GLCONTEXT::toggle_full_screen() {

        if (!_fullscreen)
            enable_full_screen();
        else
            disable_full_screen();

    }

    bool GLCONTEXT::is_fullscreen() const {

        return _fullscreen;
    }

    glm::vec2 GLCONTEXT::get_screen_resolution() const {

        return { _wndW, _wndH };
    }

    unsigned int GLCONTEXT::get_screen_width() const { 
        
        return _wndW; 
    }

    unsigned int GLCONTEXT::get_screen_height() const { 
       
        return _wndH; 
    }

    void GLCONTEXT::enable_face_culling() {

        _faceCulling = true;
        glEnable(GL_CULL_FACE);

    }

    void GLCONTEXT::disable_face_culling() {

        _faceCulling = false;
        glDisable(GL_CULL_FACE);

    }

    void GLCONTEXT::toggle_face_culling() {

        if (!_faceCulling)
            enable_face_culling();
        else 
            disable_face_culling();

    }

    void GLCONTEXT::set_window_icon(const char* path) {

        GLFWimage images[1];

        images[0].pixels = stbi_load(path, &images[0].width, &images[0].height, 0, 4);

        glfwSetWindowIcon(_window, 1, images);

        stbi_image_free(images[0].pixels);

    }

    void GLCONTEXT::set_window_title(const char* title) { 
        
        glfwSetWindowTitle(_window, title); 
    }

    void GLCONTEXT::set_console_title(const char* title) { 
        
        SetConsoleTitleA(title); 
    }

    void GLCONTEXT::show_fps_and_mspos(const char* title, const MOUSE& ms) {

        static unsigned int ticks = 0;

        ++ticks;

        if (ticks > _refreshRate / 6) {
            
            unsigned int fps = get_fps();

            std::stringstream winTitle;
            winTitle << title << fps << " fps | cursor X:" << ms.get_mouse_x() << " Y:" << ms.get_mouse_y();
            set_window_title(winTitle.str().c_str());
            
            _smoothFPS = fps;
            ticks = 0;

        }

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

        logger.clog(info.str());
        logger.clog(get_adapter_vendor(), LSUCCESS);

    }

    GLFWwindow* GLCONTEXT::get_window_handle() const { 
        
        return _window; 
    }

    HWND GLCONTEXT::get_console_handle() const {

        return _console;
    }

    int GLCONTEXT::init() {

        glfwInit();

        _monitor = glfwGetPrimaryMonitor();
        _videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        _refreshRate = _videoMode->refreshRate;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (_fullscreenBorderless) {

            glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
            glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
            glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
            
        }
        
    #ifdef __APPLE__

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    #endif

        return 0;
    }

    int GLCONTEXT::create_window() {

        _window = glfwCreateWindow(_wndW, _wndH, _wndClassName, NULL, NULL);

        if (_window == NULL) {

            PRINT_ERROR("WINDOW CREATION FAILURE (GLFWwindow == nullptr)", true, true);
            glfwTerminate();

            return -1;
        }
        else {

            logger.clog("WINDOW CREATED: ", LSUCCESS);
            std::cout << _wndClassName << '\n';

        }

        return 0;
    }

    int GLCONTEXT::set_up_and_configure() {

        glfwSetWindowPos(_window, _wndX, _wndY);
        set_window_icon(_icoPath);

        glfwMakeContextCurrent(_window);
        glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

        // Turn on vsync
        if (_swap) {

        #ifdef _WIN32
      
            typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);
            PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;

            wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(wglGetProcAddress("wglSwapIntervalEXT"));

            if (wglSwapIntervalEXT) wglSwapIntervalEXT(1);

        #else

            #define GLFW_USE_DWM_SWAP_INTERVAL
            glfwSwapInterval(swap);

        #endif

        }

        return 0;
    }

    int GLCONTEXT::load_glad() const {

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

            PRINT_ERROR("GLAD INITIALIZATION FAILED\n", false, true);

            return -1;
        }

        print_system_info();

        return 0;
    }

    int GLCONTEXT::run(void(*update)()) {

        //Root update loop
        while (!glfwWindowShouldClose(_window)) {

            if (_isTerminated) return 0;

            #ifdef PROFILE
                FrameMark("main");
            #endif
            
            frametime_calc();
            process_input(_window);

            update();

            glfwSwapBuffers(_window);
            glfwPollEvents();

            #ifdef PROFILE
                TracyGpuCollect
                TracyAllocS(update, 1, 12)
                TracyFreeS(update, 12)
            #endif

        }

        glfwTerminate();

        return 0;
    }

    void GLCONTEXT::terminate() {

        _isTerminated = true;
        glfwWindowShouldClose(_window);
        glfwTerminate();

    }

    void GLCONTEXT::process_input(GLFWwindow* window) {

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

            _isTerminated = true;
            glfwSetWindowShouldClose(window, true);

        }

    }

    void GLCONTEXT::framebuffer_size_callback(GLFWwindow*, int width, int height) { 
        
        glViewport(0, 0, width, height); 
    }

}