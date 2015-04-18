#pragma once

#include <actors/Pawn.h>
#include <physics/SphereCollider.h>
#include <components/RenderComponent.h>
#include <components/PhysicsComponent.h>
#include <cmath>

namespace sss {

    class Enemy : public engine::object::Pawn {
        private:
            typedef Pawn Super;
            typedef Enemy This;

            glm::vec3 _rotPoint;
            float _radius;
        public:
            Enemy(const glm::vec3& position, const glm::vec3& rotPoint);
            ~Enemy(); 
            void tick(float delta=1.0f) override;
            void onSpawn() override {}

    };
    
}
