#pragma once

#include <actors/Actor.h>
#include <components/RenderComponent.h>

namespace engine {
    namespace object {
       
        /**
         *
         * Most Basic renderable thing
         *
         */
        class Prop : public Actor {
            public:
                Prop(RenderComponent* render);
                virtual ~Prop();
            private:
            protected:
                typedef Actor Super;
                virtual void onDestroy() override {}

        };

    }
}
