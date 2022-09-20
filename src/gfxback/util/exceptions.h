#pragma once

#include <Windows.h>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "logger.hpp"

namespace GFXREN {

	class EXCEPTION : public std::runtime_error {

	public:

		static void print_error(const char* file, int line, const char* description, bool msgBox, bool doesThrow);

	};

}

#define PRINT_ERROR(description, msgBox, doesThrow) GFXREN::EXCEPTION::print_error(__FILE__, __LINE__, description, msgBox, doesThrow)