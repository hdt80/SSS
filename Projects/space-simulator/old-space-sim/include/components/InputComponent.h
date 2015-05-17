#pragma once

#include <unordered_map>
#include <components/Component.h>
#include <functional>
#include <input/Input.h>
#include <iostream>

namespace engine {
    namespace object {

        class InputComponent : public Component {
            private:
            public:
                InputComponent();

                virtual ~InputComponent(); 
                
                virtual void update(Actor& actor, float delta=1.0f) override;

            private:
        };

    }
}
