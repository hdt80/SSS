#pragma once

#include <components/Component.h>
#include <physics/Collideable.h>

namespace engine {
    namespace object {
       
        using physics::Collideable;

        class PhysicsComponent : public Component {
            private:
                Collideable* _collider;
            public:
                PhysicsComponent(Collideable* collider);
                virtual ~PhysicsComponent();
                virtual void update(Actor& actor, float delta=1.0f) override;

                inline const bool isCollideable() const { return _collider != nullptr; }
                inline Collideable* getCollider() const { return _collider; }
        };

    }
}
