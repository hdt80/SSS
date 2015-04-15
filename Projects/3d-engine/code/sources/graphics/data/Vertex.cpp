#include <graphics/data/Vertex.h>

namespace engine {
    namespace graphics {
        Vertex::Vertex(const glm::vec3& position, const glm::vec4& color, 
                       const glm::vec2& uv, const glm::vec3& normal) 
            : position(position), color(color), uv(uv), normal(normal) 
        {
        
        }

    }
}
