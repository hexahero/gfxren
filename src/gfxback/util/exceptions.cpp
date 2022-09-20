#include "exceptions.h"

namespace GFXREN {

	void EXCEPTION::print_error(const char* file, int line, const char* description, bool msgBox, bool doesThrow) {

		GFXREN::LOGGER<const char*>logger;

		logger.set_text_color(LERROR);

		std::cout << "ERROR\n" ;

		logger.set_text_color(LINFO);

		std::ostringstream msg;

		msg
		<< "[In] : [" << file << "]\n"
		<< "[At line] : [" << line << "]\n"
		<< "[Description] : [" << description << "]\n";

		std::cout << msg.str() << '\n';
			
		if (msgBox) 
			MessageBoxA(nullptr, msg.str().c_str(), "ERROR", MB_OK);

		if (doesThrow) 
			throw std::runtime_error(msg.str());

	}

}