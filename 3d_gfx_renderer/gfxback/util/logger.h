#pragma once

#include <Windows.h>
#include "filestream.h"

#define LINFO		15
#define LSUCCESS	10
#define LWARNING	14
#define	LERROR		12
#define	GFXRENCLR	95

namespace GFXREN {

	template<typename T>
	class LOGGER {

	public:

		LOGGER() = default;
		LOGGER(T data);
		LOGGER(T data, uint8_t logType);
		LOGGER(const char* fPath, const char* data);
		LOGGER(const char* fPath, const char* data, uint8_t logType);

		void clog(T data);
		void clog(T data, uint8_t logType);
		void write_log(const char* fPath, T data);
		void log(const char* fPath, T data, uint8_t logType);

		void set_text_color(uint8_t color);

	private:

		GFXREN::FILESTREAM<T> fileStream;
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		
	};

	template<typename T>
	LOGGER<T>::LOGGER(T data) { clog(data); }

	template<typename T>
	LOGGER<T>::LOGGER(T data, uint8_t logType) {

		set_text_color(logType),
		clog(data),
		set_text_color(LINFO);

	}

	template<typename T>
	LOGGER<T>::LOGGER(const char* fPath, const char* data) { 
		
		log(fPath, data, LINFO); 
	}

	template<typename T>
	LOGGER<T>::LOGGER(const char* fPath, const char* data, uint8_t logType)  { 
		
		log(fPath, data, logType); 
	}

	template<typename T>
	void LOGGER<T>::clog(T data) { 
		
		std::cout << data << '\n'; 
	}

	template<typename T>
	void LOGGER<T>::clog(T data, uint8_t logType) {

		set_text_color(logType);
		std::cout << data << '\n';
		set_text_color(LINFO);

	}

	template<typename T>
	void LOGGER<T>::write_log(const char* fPath, T data) {

		fileStream.write(fPath, data); 
	}

	template<typename T>
	void LOGGER<T>::log(const char* fPath, T data, uint8_t logType) {

		clog(data, logType);
		fileStream.write(fPath, data);

	}

	template<typename T>
	void LOGGER<T>::set_text_color(uint8_t color) { 
		
		SetConsoleTextAttribute(consoleHandle, color); 
	}

}