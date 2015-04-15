#include <physics/SphereCollider.h>

namespace engine {
    namespace physics {
        
        SphereCollider::SphereCollider(const glm::vec3& position, float radius) 
            : Super(position, SPHERE), _radius(radius)
        {
        
        }
    
        bool SphereCollider::collides(const Collideable& other) {
            const SphereCollider* p = dynamic_cast<const SphereCollider*>(&other);
            if(p != nullptr)
                return (glm::length(_position - other.getPosition()) <= _radius + p->getRadius());
            // TODO: add the ability to collide with other objects
            return false;
        }

        glm::vec3 SphereCollider::getDirection(const Collideable& other) {
            return _position - other.getPosition();
        } 
    }
}
