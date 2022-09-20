#pragma once

#include <sstream>

#include "../util/exceptions.h"
#include "../util/logger.hpp"

#include <glad.h>
#include <GLFW/glfw3.h>

namespace {

    void gl_clear_err() {

        while (glGetError() != GL_NO_ERROR);
    }

    void gl_check_err() {

        std::ostringstream msg;

        while (GLenum errmsg = glGetError()) {

            msg << errmsg;
            PRINT_ERROR(msg.str().c_str(), false, false);

        }

    }

    bool gl_err_log(const char* file, int line) {

        GFXREN::LOGGER<const char*> logger;

        while (GLenum errmsg = glGetError()) {

            logger.set_text_color(LERROR);

            std::cout << "[GL ERROR] ";

            logger.set_text_color(LINFO);

            std::cout
                << "|" << errmsg << "| "
                << "FILE |" << file << "| "
                << "LINE |" << line << "|"
                << std::endl;

            return false;
        }

        return true;
    }

}

namespace GFXREN {

	#define ASSERT(x) if (!(x)) __debugbreak();
	
	#define GL_TRY(x)                               \
	gl_clear_err();                                 \
	x;                                              \
	ASSERT(gl_err_log(__FILE__, __LINE__))          \

}