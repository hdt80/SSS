#pragma once

#include <actors/Pawn.h>
#include <physics/SphereCollider.h>
#include <components/RenderComponent.h>

namespace sss {
    
    class Missile : public engine::object::Pawn {
        private:
            typedef Pawn Super;
            typedef Missile This;

            glm::vec3 _vector;
        public:
            Missile(const glm::vec3& position, const glm::vec3& vector);
            ~Missile();

            void tick(float delta=1.0f) override;
    };

}
