#pragma once

#include <glm/glm.hpp>

namespace engine {
    namespace physics {

        class Collideable {
            protected:
                enum {
                    AABB, 
                    SPHERE,
                    NONE
                };
                glm::vec3 _position; 
                const char _type;

            public:
                
                virtual ~Collideable();

                virtual bool collides(const Collideable& other) const;
                virtual glm::vec3 getDirection(const Collideable& other);

                inline const char getType() const { return _type; }
                inline const glm::vec3& getPosition() const { return _position; }
                inline void setPosition(const glm::vec3& position) { _position = position; }
            protected:
                Collideable(const glm::vec3& position, char type=NONE);

        };

    }
}
