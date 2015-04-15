#pragma once

#include <vector>
#include <graphics/data/Vertex.h>
#include <graphics/data/Mesh.h>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

namespace engine {
    namespace utils {

        using graphics::Vertex;
        using graphics::Mesh;
        class MeshUtils {
            private:
                typedef struct {
                    unsigned int vIndex; // vertex index
                    unsigned int uIndex; // UV index
                    unsigned int nIndex; // normal index
                    bool hasUV;
                    bool hasNM; // has normal
                } OBJIndex;
            public:
                static bool load_mesh_obj(const std::string& file_path, std::vector<Vertex>& vertices_out, 
                                          std::vector<GLuint>& indices_out);

                static bool load_mesh_bin(const std::string& file_path, std::vector<Vertex>& vertices_out, 
                                          std::vector<GLuint>& indices_out);

                static bool write_mesh(const std::string& file_path, const Mesh& mesh);

            private:
                static std::vector<std::string> split_spaces(const std::string& str);
                static OBJIndex parse_obj_index(const std::string& token);

                static glm::vec4 random_color() ; 
        };
    }
}
