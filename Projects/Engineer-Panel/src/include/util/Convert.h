#ifndef UTIL_CONVERT_H
#define UTIL_CONVERT_H

#include <string>
#include <sstream>

#include "util/Logger.h"

namespace convert {
	template<typename T> 
	std::string toString(const T& n) {
		std::ostringstream stream;
		stream << n;
		return stream.str();
	}
}

#endif