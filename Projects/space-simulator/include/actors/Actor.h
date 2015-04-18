#pragma once

#include <graphics/data/Transform.h>
#include <graphics/data/Mesh.h>
#include <vector>

namespace engine {
    namespace object {

        

        class Component;
        class RenderComponent;
        class Actor {
            protected:
                bool _pendingKill;
                std::vector<Component*> _components;
                graphics::Transform _transform;
                RenderComponent* _render; 
            public:
                Actor();
                virtual ~Actor();

                inline bool isPendingKill() const { return _pendingKill; }
                /* calls onDestroy, sets pending kill to true*/
                void destroy();
                
                /* this will go through and update the components */
                virtual void tick(float delta=1.0f);

                /* called when added to a scene */
                virtual void onSpawn();
               
                /* implements transforms functions */
                inline const glm::mat4 getTransformation() const { return _transform.getTransformation(); }
                inline const glm::vec3 getPosition() const { return _transform.getPosition(); }
                inline const glm::quat getRotation() const { return _transform.getRotation(); }
                inline void  setPosition(const glm::vec3& position) { _transform.setPosition(position); }
                inline void setRotation(const glm::quat& rotation) {_transform.setRotation(rotation); }
                inline void  move(const glm::vec3& delta) { _transform.translate(delta); }
                inline void  rotate(const glm::vec3& axis, float theta) { _transform.rotate(axis, theta); }

                /* can the actor be rendered and render */
                inline bool isRenderable() const { return _render != nullptr; }
                inline const RenderComponent* getRenderComponent() const { return _render; }

            private:
                typedef Actor This;
            protected:
                virtual void onDestroy();
        };
    }
}
