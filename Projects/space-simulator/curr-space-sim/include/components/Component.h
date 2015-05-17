#pragma once

#include <actors/Actor.h>

namespace engine {
    namespace object {
     
       
        class Component {
            private:
            public:
                virtual void update(Actor& actor, float delta=1.0f) = 0;
            protected:
        };

    }
}
