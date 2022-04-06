#pragma once

#include <Windows.h>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "logger.h"

namespace GFXREN {

	class EXCEPTION : public std::runtime_error {

	public:

		static void print_exception(const char* file, int line, const char* description, bool msgBox);

	};

}

#define EXCEPTION(description, msgBox) GFXREN::EXCEPTION::print_exception(__FILE__, __LINE__, description, msgBox);