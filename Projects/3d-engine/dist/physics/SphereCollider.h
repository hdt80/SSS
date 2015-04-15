#pragma once

#include <physics/Collideable.h>

namespace engine {
    namespace physics {
            
        class SphereCollider : public Collideable {
            private:
                const float _radius;
            public:

                /* The position is the center of the object */
                SphereCollider(const glm::vec3& position, float radius);

                inline const float getRadius() const { return _radius; }
                bool collides(const Collideable& other) override;
                glm::vec3 getDirection(const Collideable& other) override;
            private:
                typedef Collideable Super;
            protected:
        };

    }
}
