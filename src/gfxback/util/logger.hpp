#pragma once

#include <Windows.h>
#include "filestream.hpp"

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
		LOGGER(const T& data);
		LOGGER(const T& data, uint8_t logType);
		LOGGER(const char* fPath, const char* data);
		LOGGER(const char* fPath, const char* data, uint8_t logType);

		void clog(const T& data);
		void clog(const T& data, uint8_t logType);
		void write_log(const char* fPath, const T& data);
		void log(const char* fPath, const T& data, uint8_t logType);

		void set_text_color(uint8_t color);

	private:

		GFXREN::FILESTREAM<T>	_fileStream;
		HANDLE					_consoleHandle;
		
	};

	template<typename T>
	LOGGER<T>::LOGGER(const T& data)
		:
		_consoleHandle(GetStdHandle(STD_OUTPUT_HANDLE))
	{ 
		
		clog(data); 
	}

	template<typename T>
	LOGGER<T>::LOGGER(const T& data, uint8_t logType)
		:
		_consoleHandle(GetStdHandle(STD_OUTPUT_HANDLE))
	{

		set_text_color(logType),
		clog(data),
		set_text_color(LINFO);

	}

	template<typename T>
	LOGGER<T>::LOGGER(const char* fPath, const char* data) 
		:
		_consoleHandle(GetStdHandle(STD_OUTPUT_HANDLE))
	{ 
		
		log(fPath, data, LINFO); 
	}

	template<typename T>
	LOGGER<T>::LOGGER(const char* fPath, const char* data, uint8_t logType)
		:
		_consoleHandle(GetStdHandle(STD_OUTPUT_HANDLE))
	{ 
		
		log(fPath, data, logType); 
	}

	template<typename T>
	void LOGGER<T>::clog(const T& data) { 
		
		std::cout << data << '\n'; 
	}

	template<typename T>
	void LOGGER<T>::clog(const T& data, uint8_t logType) {

		set_text_color(logType);
		std::cout << data << '\n';
		set_text_color(LINFO);

	}

	template<typename T>
	void LOGGER<T>::write_log(const char* fPath, const T& data) {

		_fileStream.write(fPath, data); 
	}

	template<typename T>
	void LOGGER<T>::log(const char* fPath, const T& data, uint8_t logType) {

		clog(data, logType);
		_fileStream.write(fPath, data);

	}

	template<typename T>
	void LOGGER<T>::set_text_color(uint8_t color) { 
		
		SetConsoleTextAttribute(_consoleHandle, color); 
	}

}