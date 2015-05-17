#pragma once

#include "Vertex.h"
#include <vector>
#include <graphics/buffers/Buffers.h>
#include <GL/glew.h>

namespace engine {
    namespace graphics {
       

        struct Mesh {
            const std::vector<Vertex> vertices; 
            const std::vector<GLuint> indices;  
            const GLuint vertexCount;
            const GLuint indexCount;

            Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
            std::vector<Vertex> getTransformedMesh(const glm::mat4& transform);

            static VertexArray constructVAO(const Mesh& mesh);
        };

        
    }
}
