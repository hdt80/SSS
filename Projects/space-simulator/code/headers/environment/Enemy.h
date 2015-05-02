#pragma once

#include <actors/Pawn.h>
#include <physics/SphereCollider.h>
#include <components/RenderComponent.h>
#include <components/PhysicsComponent.h>
#include <cmath>
#include <core/Parametric.h>
#include <glm/trigonometric.hpp>

namespace sss {

    class Enemy : public engine::object::Pawn {
        private:
            typedef Pawn Super;
            typedef Enemy This;

            Parametric* _course;

        public:
            Enemy(const glm::vec3& position, Parametric* course);
            ~Enemy(); 
            void tick(float delta=1.0f) override;
            void onSpawn() override {}

    };
    
}
