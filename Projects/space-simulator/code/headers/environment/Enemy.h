#pragma once

#include <actors/Pawn.h>
#include <physics/SphereCollider.h>
#include <components/RenderComponent.h>
#include <components/PhysicsComponent.h>
#include <cmath>
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

            std::string _id;
        public:
            Enemy(const glm::vec3& position, Parametric* course);
            ~Enemy(); 
            void tick(float delta=1.0f) override;
            void onSpawn() override {}

            inline void setID(const std::string& id) { _id = id; }

            void onHit();
        private:
            void movement(float delta=1.0f);
            void fire(float delta=1.0f);
            bool canFire();
    };
    
}
