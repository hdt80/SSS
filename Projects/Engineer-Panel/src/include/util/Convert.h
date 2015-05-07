#ifndef UTIL_CONVERT_H
#define UTIL_CONVERT_H

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

#include "util/Logger.h"

namespace convert {
	template<typename T> 
	std::string toString(const T& n) {
		std::ostringstream stream;
		stream << n;
		return stream.str();
	}

	// Split a string into a vector delimited by the delim char
	std::vector<std::string> split(std::string str, char delim);
	// Convert a string to an int
	int toInt(std::string str);
}

#endif