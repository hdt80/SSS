#pragma once

#include <glm/glm.hpp>

namespace engine {
    namespace graphics {
        
        struct Vertex {
            
            glm::vec3 position;
            glm::vec4 color;
            glm::vec2 uv;
            glm::vec3 normal;

            Vertex() {}
            Vertex(const glm::vec3& position, const glm::vec4& color, 
                   const glm::vec2& uv=glm::vec2(0, 0), const glm::vec3& normal=glm::vec3(0, 0, 0));

        };

#define VERTEX_SIZE sizeof(Vertex) 

    }
}
