#pragma once

#include <actors/Pawn.h>
#include <input/Input.h>
#include <physics/SphereCollider.h>
#include <components/RenderComponent.h>
#include <core/event_queue.h>

namespace sss {

    using engine::object::Pawn;
    using engine::object::Actor;
    using engine::Input;

    class Player : public Pawn {
        public:
            enum {
                ENGINE_POWER,
                SHIELD_POWER,
                NUM_POWER_COMPS,
            };
        private:
            typedef Pawn Super;
            typedef Player This;
            float _power[NUM_POWER_COMPS];

        public:

            Player(const glm::vec3& position=glm::vec3(0, 0, 0));
            ~Player();

            void tick(float delta=1.0f) override;
            void onSpawn() override;

            void handleEvent(const sss_event& evt);
            
            inline float& operator[](int index) { return _power[index]; }
            inline float operator[](int index) const { return _power[index]; }

            inline glm::vec3 getForward() const { return glm::mat3_cast(getRotation()) * glm::vec3(0, 0, 1); }
            inline glm::vec3 getRight() const { return glm::mat3_cast(getRotation()) * glm::vec3(1, 0, 0); }
            inline glm::vec3 getUp() const { return glm::mat3_cast(getRotation()) * glm::vec3(0, 1, 0); }

        protected:
            void onDestroy() override;
    };


    class PlayerInput : public engine::object::InputComponent {
        public:
            PlayerInput();
            ~PlayerInput();

            void update(Actor& actor, float delta=1.0f) override;
        private:
            typedef engine::object::InputComponent Super;
            typedef PlayerInput This;
        protected:
    };
}
