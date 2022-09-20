#pragma once 

#include <fstream>

namespace GFXREN {

	template<typename T>
	class FILESTREAM {

	public:

		FILESTREAM();
		FILESTREAM(const char* fPath, const T& data);

		void write();
		void write(const char* fPath, const T& data);

	private:

		std::fstream	_fileStream;	
		std::ofstream	_fileOut;		
		std::ifstream	_fileIn;		

		const char* _filePath;
		T			_data;

	};

	template<typename T>
	FILESTREAM<T>::FILESTREAM() : _filePath("log.txt"), _data("empty data") 
	{}

	template<typename T>
	FILESTREAM<T>::FILESTREAM(const char* fPath, const T& data) : _filePath(fPath), _data(data) { 
		
		write(); 
	}

	template<typename T>
	void FILESTREAM<T>::write() {

		_fileStream.open(_filePath, std::fstream::in | std::fstream::out | std::fstream::app);
		_fileStream << _data << "\n";

	}

	template<typename T>
	void FILESTREAM<T>::write(const char* fPath, const T& data) {

		_fileStream.open(fPath, std::fstream::in | std::fstream::out | std::fstream::app);
		_fileStream << data << "\n";

	}

}
