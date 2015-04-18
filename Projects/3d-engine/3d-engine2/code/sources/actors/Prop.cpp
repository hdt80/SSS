#include <actors/Prop.h>

namespace engine {
    namespace object {
        
        Prop::Prop(RenderComponent* render) : Super() {
            _render = render;
        }

        Prop::~Prop() {
            delete _render;
            _render = nullptr;
        }
    }
}
