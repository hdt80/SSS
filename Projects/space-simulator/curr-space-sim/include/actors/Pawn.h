#pragma once
#include <actors/Actor.h>
#include <components/InputComponent.h>
#include <components/PhysicsComponent.h>

namespace engine {
    namespace object {
        
        class Pawn : public Actor {
            private:
                typedef Actor Super;
            protected: 
                InputComponent* _input;
                PhysicsComponent* _physics;

            public:
                Pawn();
                virtual ~Pawn();
                virtual void tick(float delta=1.0f) override;
                virtual void onSpawn() override;

                const Collideable* getCollider();

            protected:
                virtual void bindKeys();
                virtual void onDestroy() override;
        };
    }
}
