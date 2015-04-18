#pragma once

#include <string>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
#include <string.h>

namespace engine {
    namespace utils {

        /**
         * @param file_path - path to the file to be read
         *
         * @return the contents of the given file
         */
        std::string read_file(const std::string& file_path);
    }   
}
