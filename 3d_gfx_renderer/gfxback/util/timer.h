#pragma once

#include <iostream>
#include <chrono>
#include <sstream>

namespace GFXREN {

	class TIMER {
	
	public:

		TIMER();
		TIMER(const char* message);
		TIMER(const char* message, const char* fileName);
	   ~TIMER();

		void start();
		double stop();
		void print_time();
		double peek_time();
		inline double get_time() const;

		inline std::string format(double time) const;

	private:

		std::chrono::time_point<std::chrono::steady_clock> timerStart;
		std::chrono::time_point<std::chrono::steady_clock> timerStop;
		double time = 0.0f;

		const char* message;
		const char* fileName;

	};

}