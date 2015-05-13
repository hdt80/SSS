#ifndef UTIL_LOGGER_H
#define UTIL_LOGGER_H

#include <stdio.h>   // vfprintf
// #include <iostream>
// #include <locale>
// #include <stdarg.h>  // va_list, ...
// #include <vector> 	 // std::vector

// This is a comment to make bryce shut the fuck up about my lack of comments
// \x1b[037m           - Change the text color to white
// \x1b[1m             - Light gray
// \x1b[0m             - Reset back to the previous color, white
// \x1b[1m             - Light gray again
// \x1b[35m            - Magenta
// \x1b[0m             - Reset color back to white
// S                   - char* provided
// __FILE__            - This will be replaced with the file it's ine 
// __LINE__            - Line number in the file
// __PRETTY_FUNCTION__ - Prettyify the function it's ran from
// ##__VA_ARGS__       - ... , the formated array of elemts to replace

#ifdef SSS_DO_DEBUG
	#define debug(S, ...)

	#define info(S, ...) fprintf(stderr, \
		"\x1b[037m\x1b[1m[\x1b[32mINFO\x1b[0m] " S "\n", ##__VA_ARGS__)

	#define warn(S, ...) fprintf(stderr, \
		"\x1b[037m\x1b[1m[\x1b[33mWARN\x1b[0m] " S "\n", ##__VA_ARGS__)

	#define error(S, ...) fprintf(stderr, \
		"\x1b[037m\x1b[1m[\x1b[31mERROR\x1b[0m] " S "\n", ##__VA_ARGS__)
#else
	#define debug(S, ...) fprintf(stderr,                                \
	 	"\x1b[037m\x1b[1m(%s:%d, %s)\x1b[0m\n\x1b[1m[\x1b[35mDEBUG\x1b[0m] " S "\n", \
	 	__FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)

	#define info(S, ...) fprintf(stderr,                                \
 		"\x1b[037m\x1b[1m(%s:%d, %s)\x1b[0m\n\x1b[1m[\x1b[32mINFO\x1b[0m] " S "\n", \
  		__FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)

	#define warn(S, ...) fprintf(stderr,                                \
 		"\x1b[037m\x1b[1m(%s:%d, %s)\x1b[0m\n\x1b[1m[\x1b[33mWARN\x1b[0m] " S "\n", \
		__FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)

	#define error(S, ...) fprintf(stderr,                                \
		"\x1b[037m\x1b[1m(%s:%d, %s)\x1b[0m\n\x1b[1m[\x1b[31mERROR\x1b[0m] " S "\n", \
		__FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)
#endif

#endif