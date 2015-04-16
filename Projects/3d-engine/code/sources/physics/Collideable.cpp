#include <physics/Collideable.h>
#include <iostream>

namespace engine {
    namespace physics {
        
        Collideable::Collideable(const glm::vec3& position, char type) 
            : _position(position), _type(NONE) 
        {
        }

        Collideable::~Collideable() {
        }

        bool Collideable::collides(const Collideable& other) const {
            return (_position == other.getPosition());
        }
       
        glm::vec3 Collideable::getDirection(const Collideable& other) {
            return glm::vec3(0, 0, 0);   
        }
    }
}
