#include <graphics/data/Mesh.h>


namespace engine {
    namespace graphics {
     
        Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) 
            : vertices(vertices), indices(indices), vertexCount(vertices.size()), indexCount(indices.size())
        {}

               
        std::vector<Vertex> Mesh::getTransformedMesh(const glm::mat4& transform) {
            std::vector<Vertex> result = vertices;
           
            for(unsigned int i = 0; i < vertexCount; i++) {
                glm::vec3 curr = vertices[i].position;
                // result[i].position = glm::vec3(transform * glm::vec4(curr, 1));
            } 

            return result;
        }

        VertexArray Mesh::constructVAO(const Mesh& mesh) {
            VertexArray vao;
            
            std::vector<GLfloat> fs;
            std::vector<GLfloat> cs;

            for(unsigned int i = 0; i < mesh.vertexCount; i++) {
                glm::vec3 curr = mesh.vertices[i].position;
                fs.push_back(curr.x); fs.push_back(curr.y); fs.push_back(curr.z);
                glm::vec4 currC = mesh.vertices[i].color;
                cs.push_back(currC.x); cs.push_back(currC.y); cs.push_back(currC.z); cs.push_back(currC.w);
            } 
            
            vao.addBuffer(new Buffer(&fs[0], fs.size(), 3), 0);
            vao.addBuffer(new Buffer(&cs[0], cs.size(), 4), 1);


            return vao;
        }

    }
} 
