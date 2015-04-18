#include <utils/FileUtils.h>

namespace engine {
    namespace utils { 
        std::string read_file(const std::string& file_path) {
            FILE* file = fopen(file_path.c_str(), "rt");
            if(not file) {
                printf("Could Not Open File: %s\n", file_path.c_str());
                return "Error";
            }
            fseek(file, 0, SEEK_END);
            unsigned long length = ftell(file);
            char* data = new char[length + 1];
            memset(data, 0, length + 1);
            fseek(file, 0, SEEK_SET);
            fread(data, 1, length, file);
            fclose(file);
            std::string result(data);
            delete[] data;

            return result;
        }

    }
}
