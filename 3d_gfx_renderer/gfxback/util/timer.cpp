#include "timer.h"

namespace GFXREN {

	TIMER::TIMER() : message(NULL), fileName(NULL) { start(); }

	TIMER::TIMER(const char* message) : message(message), fileName(NULL) { start(); }

	TIMER::TIMER(const char* message, const char* fileName) : message(message), fileName(fileName) { start(); }

	TIMER::~TIMER() { if (message != 0) { print_time(); } }

	void TIMER::start() { timerStart = std::chrono::high_resolution_clock::now(); }

	double TIMER::stop() {
	
		timerStop = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> time = timerStop - timerStart;

		this->time = time.count();

		return time.count();

	}

	void TIMER::print_time() {  

		if (message == NULL) {

			stop();
			std::cout << format(time) << "s" << std::endl;

		}

		if (message != NULL) {

			stop();
			std::cout << message << format(time) << "s" << std::endl;

		}

	}

	double TIMER::peek_time() {

		std::chrono::time_point<std::chrono::steady_clock> timerNow = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> timePeek = timerNow - timerStart;
		
		return timePeek.count();
	}

	double TIMER::get_time() const { return time; }


	std::string TIMER::format(double time) const {

		std::ostringstream oss;
		oss << std::fixed << time;

		return oss.str();
	}

}