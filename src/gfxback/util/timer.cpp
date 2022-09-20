#include "timer.h"

namespace GFXREN {

	TIMER::TIMER() 
		:
		_time{ 0.0f },
		_message(), 
		_fileName()
	{ 
		
		start(); 
	}

	TIMER::TIMER(const char* message) 
		:
		_time{ 0.0f },
		_message(message), 
		_fileName()
	{ 
		
		start(); 
	}

	TIMER::TIMER(const char* message, const char* fileName) 
		:
		_time{ 0.0f },
		_message(message), 
		_fileName(fileName)
	{ 
		
		start(); 
	}

	TIMER::~TIMER() { 
		
		if (_message != 0) { 
			
			print_time(); 
		} 

	}

	void TIMER::start() { 
		
		_timerStart = std::chrono::high_resolution_clock::now(); 
	}

	double TIMER::stop() {
	
		_timerStop = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> time = _timerStop - _timerStart;

		_time = time.count();

		return time.count();

	}

	void TIMER::print_time() {  

		if (_message == NULL) {

			stop();
			std::cout << format(_time) << "s" << std::endl;

		}

		if (_message != NULL) {

			stop();
			std::cout << _message << format(_time) << "s" << std::endl;

		}

	}

	double TIMER::peek_time() const {

		std::chrono::time_point<std::chrono::steady_clock> timerNow = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> timePeek = timerNow - _timerStart;
		
		return timePeek.count();
	}

	double TIMER::get_time() const { return _time; }


	std::string TIMER::format(double time) const {

		std::ostringstream oss;
		oss << std::fixed << time;

		return oss.str();
	}

}