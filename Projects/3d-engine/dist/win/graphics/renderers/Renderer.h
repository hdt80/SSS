#pragma once

#include <actors/Actor.h>
#include <components/RenderComponent.h>
#include <algorithm>    // std::transform

namespace engine {
    namespace graphics {
   
        using object::Actor;
         
        class Renderer {
            public:
            private:
            protected:
                virtual void submit(const Actor* actor) = 0;
                virtual void flush() = 0;
                
                typedef struct VP {
                    glm::vec3 position;
                    unsigned int color;
                    float texture_id;
                    glm::vec2 uv;
                    glm::vec3 normal;
                    /* This is all one transformation */
                    glm::vec4 transformX;
                    glm::vec4 transformY;
                    glm::vec4 transformZ;
                    glm::vec4 transformW;
                } VertexPointer;

        };
    

    }
}
