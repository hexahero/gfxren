#pragma once 

#include <fstream>

namespace GFXREN {

	template<typename T>
	class FILESTREAM {

	public:

		FILESTREAM();
		FILESTREAM(const char* fPath, T data);

		void write();
		void write(const char* fPath, T data);

	private:

		std::fstream fileStream;	
		std::ofstream fileOut;		
		std::ifstream fileIn;		

		const char* filePath;
		T data;

	};

	template<typename T>
	FILESTREAM<T>::FILESTREAM() : filePath("log.txt"), data("empty data") {}

	template<typename T>
	FILESTREAM<T>::FILESTREAM(const char* fPath, T data) : filePath(fPath), data(data) { write(); }

	template<typename T>
	void FILESTREAM<T>::write() {

		fileStream.open(filePath, std::fstream::in | std::fstream::out | std::fstream::app);
		fileStream << data << "\n";

	}

	template<typename T>
	void FILESTREAM<T>::write(const char* fPath, T data) {

		fileStream.open(fPath, std::fstream::in | std::fstream::out | std::fstream::app);
		fileStream << data << "\n";

	}

}
