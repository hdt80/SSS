#include <actors/Actor.h>
#include <components/Component.h>
#include <components/RenderComponent.h>

namespace engine {
    namespace object {
       
        Actor::Actor() {
            _pendingKill = false;
            _render = nullptr;
        }

        Actor::~Actor() {
        }

        void Actor::tick(float delta) {
            for(auto& c : _components)
                c->update(*this, delta);
        }

        void Actor::onSpawn() {
            
        }
            
        void Actor::destroy() {
            /* don't want to be destroied more than once */
            if(_pendingKill)
                return;
            _pendingKill = true;
            onDestroy();
        }

        void Actor::onDestroy() {
            
        }

    }
}
