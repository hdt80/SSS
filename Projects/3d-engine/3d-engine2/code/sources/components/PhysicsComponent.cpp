#include <components/PhysicsComponent.h>

namespace engine {
    namespace object {
        PhysicsComponent::PhysicsComponent(Collideable* collider) 
            : _collider(collider)
        {
        
        }

        PhysicsComponent::~PhysicsComponent() {
            delete _collider;
        }

        void PhysicsComponent::update(Actor& actor, float delta) {
        
        }
    }
}
