#pragma once

#include <string>
#include <algorithm>  
#include <Windows.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "../util/exceptions.h"

#define GFXREN_INVALID_FILE_PATH "INVALID_FILE_PATH"

namespace GFXREN {

namespace UTIL {

	std::string get_file_extension(const std::string& path);
	std::string get_file_name(const std::string& path);
	std::string get_relative_path(const std::string& targetDirectory);
	std::string get_file_via_dialog(GLFWwindow* parentWindowHandle);
	std::string normalize_file_path(std::string& path);
	
}

}