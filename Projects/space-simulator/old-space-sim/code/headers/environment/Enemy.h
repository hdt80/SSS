#pragma once

#include <actors/Pawn.h>
#include <physics/SphereCollider.h>
#include <components/RenderComponent.h>
#include <components/PhysicsComponent.h>
#include <cmath>
#include <sstream>
#include <core/Parametric.h>
#include <glm/trigonometric.hpp>
#include <core/Timer.h>

namespace sss {

    class Game;

    class Enemy : public engine::object::Pawn {
        private:
            typedef Pawn Super;
            typedef Enemy This;

            Parametric* _course;
            Timer* _timer;

            size_t _id;

            static size_t ID;
        public:
            Enemy(const glm::vec3& position, Parametric* course);
            ~Enemy(); 
            void tick(float delta=1.0f) override;
            void onSpawn() override {}
            
            void onDestroy() override;

            void onHit();
        private:
            void movement(float delta=1.0f);
            void fire(float delta=1.0f);
            bool canFire();
    };
    
}
