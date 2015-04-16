#include <actors/Pawn.h>

namespace engine {
    namespace object {
        Pawn::Pawn() : Super() {
            _input = new InputComponent;
            _physics = new PhysicsComponent(nullptr);
        }

        Pawn::~Pawn() {
            delete _input;
            delete _physics;

            _input = nullptr;
            _physics = nullptr;
        }

        void Pawn::tick(float delta) {
        
        }

        void Pawn::onSpawn() {
            
        }

        void Pawn::bindKeys() {
            
        }

        void Pawn::onDestroy() {
        
        }

        const Collideable* Pawn::getCollider() {
            _physics->getCollider()->setPosition(getPosition());
            return _physics->getCollider();
        }

    }
}
