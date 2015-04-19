#include <utils/MeshUtils.h>

namespace engine {
    namespace utils {
       
        /* TODO: make better */
        bool MeshUtils::load_mesh_obj(const std::string& file_path, std::vector<Vertex>& vertices_out, std::vector<GLuint>& indices_out) {
          
            std::ifstream file(file_path);
            
            if(not file.is_open())
                return false;
            std::string line;
            std::vector<OBJIndex> indices;
            std::vector<glm::vec3> temp_verts;
            std::vector<glm::vec2> temp_uvs;
            std::vector<glm::vec3> temp_normals;

            while(file.good()) {
                std::getline(file, line);
                if(line.empty())
                    continue;

                std::vector<std::string> tokens = split_spaces(line);
                /* parse a vertex */
                if(not tokens[0].compare("v")) { 
                    glm::vec3 vert;
                    std::sscanf(tokens[1].c_str(), "%f", &vert.x);
                    std::sscanf(tokens[2].c_str(), "%f", &vert.y);
                    std::sscanf(tokens[3].c_str(), "%f", &vert.z);
                    temp_verts.push_back(vert);
                } else if(not tokens[0].compare("vt")) { /* parse a UV coordinate */
                    glm::vec2 UV;
                    std::sscanf(tokens[1].c_str(), "%f", &UV.x);
                    // UV.x = std::stof(tokens[1]);i
                    std::sscanf(tokens[2].c_str(), "%f", &UV.y);
                    UV.y = 1.0f - UV.y;
                    // UV.y = 1.0f - std::stof(tokens[2]);
                    temp_uvs.push_back(UV);
                } else if(not tokens[0].compare("f")) { /* parse a face */
                    for(size_t i = 0; i < tokens.size() - 3; i++) {
                        indices.push_back(parse_obj_index(tokens[1]));
                        indices.push_back(parse_obj_index(tokens[2 + i]));
                        indices.push_back(parse_obj_index(tokens[3 + i]));
                    }
                }
            }
            file.close();
            /* calculate all the normals */
            for(size_t i = 0; i < temp_verts.size(); i+= 3) {
                short i0 = i;
                short i1 = i + 1;
                short i2 = i + 2;

                glm::vec3 normal = glm::normalize(glm::cross(
                    glm::vec3(temp_verts[i1]) - glm::vec3(temp_verts[i0]),
                    glm::vec3(temp_verts[i2]) - glm::vec3(temp_verts[i0])
                ));
                temp_normals.push_back(normal);
                temp_normals.push_back(normal);
                temp_normals.push_back(normal);
            }

            for(size_t i = 0; i < indices.size(); i++) {
                glm::vec3 position = glm::vec3(temp_verts[indices[i].vIndex]); // The OBJ format starts indicies at one

                glm::vec4 color = random_color(); //  (indices[i].hasUV) ? glm::vec4(0, 0, 0, 1) : random_color();
                glm::vec2 uv    = indices[i].hasUV ? temp_uvs[indices[i].uIndex] : glm::vec2(0, 0);
                glm::vec3 norm  = temp_normals[indices[i].vIndex];
                vertices_out.push_back(Vertex(position, color, uv, norm));
                indices_out.push_back(i);
            }

            return true;
        }

        bool MeshUtils::write_mesh(const std::string& file_path, const Mesh& mesh) {
            std::ofstream file(file_path, std::ios::out| std::ios::binary);
            if(not file.is_open()) {
                std::cerr << "Could not open file: " << file_path << std::endl;
                return false;
            }
            size_t vertexCount = mesh.vertexCount;
            /* write the number of vertices to the file */
            file.write(reinterpret_cast<const char*>(&vertexCount), sizeof(vertexCount));
            /* write the vertices to the file */
            file.write(reinterpret_cast<const char*>(&mesh.vertices[0]), vertexCount * sizeof(Vertex));
            size_t indexCount = mesh.indexCount;
            /* write the number of indices to the file */
            file.write(reinterpret_cast<const char*>(&indexCount), sizeof(indexCount));
            /* write the indices to the file */
            file.write(reinterpret_cast<const char*>(&mesh.indices[0]), indexCount * sizeof(GLuint));
            file.close();
            return true;
        }
       
        bool MeshUtils::load_mesh_bin(const std::string& file_path, std::vector<Vertex>& vertices_out, std::vector<GLuint>& indices_out) {
            std::ifstream file(file_path, std::ios::in | std::ios::binary);
            if(not file.is_open()) {
                std::cerr << "Could not open file: " << file_path << std::endl;
                return false;
            }
            Vertex* vertices;
            size_t vertexCount;
            /* read the number of vertices from the file */
            file.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));
            vertices = new Vertex[vertexCount];
            
            /* read in all of the vertices from the file */
            file.read(reinterpret_cast<char*>(&vertices[0]), vertexCount * sizeof(Vertex));
            
            GLuint* indices;
            size_t indexCount;
            /* read in the number of indices */
            file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));
            indices = new GLuint[indexCount];
            /* read in the indices */
            file.read(reinterpret_cast<char*>(&indices[0]), indexCount * sizeof(GLuint));
            file.close();
            for(size_t i = 0; i < vertexCount; i++) 
                vertices_out.push_back(vertices[i]);
            for(size_t i = 0; i < indexCount; i++)
                indices_out.push_back(indices[i]);

            delete[] indices;
            delete[] vertices;

            return true;
        }
        

        MeshUtils::OBJIndex MeshUtils::parse_obj_index(const std::string& token) {
            OBJIndex index{0, 0, 0, false, false};
            std::vector<unsigned int> nums;
            std::string num;
            for(size_t i = 0; i < token.length(); i++) {
                if(token[i] == '/') {
                    int n = 0;
                    std::sscanf(num.c_str(), "%d", &n);
                    nums.push_back(n - 1);
                    num = "";
                } else {
                    num += token[i];
                }
            }

            index.vIndex = nums[0];

            if(nums.size() > 1) {
                index.hasUV = true;
                index.uIndex = nums[1];
                if(nums.size() > 2) {
                    index.hasNM = true;
                    index.nIndex = nums[2];
                }
            }

            return index;
        }

        std::vector<std::string> MeshUtils::split_spaces(const std::string& str) {
            std::vector<std::string> result;
            std::stringstream ss(str);
            std::string buffer;
            while(ss >> buffer)
                result.push_back(buffer);
            return result;
        }

        glm::vec4 MeshUtils::random_color() {
            return glm::vec4(
                rand() % 1000 / 1000.0f,
                rand() % 1000 / 1000.0f,
                rand() % 1000 / 1000.0f,
                1
            ); 
        }

    } // end namespace utils
}
