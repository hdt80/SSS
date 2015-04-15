#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

namespace engine {
    namespace graphics {
        class Camera {
            private:
                glm::mat4 _perspective;
                glm::vec3 _position;
                glm::quat _rotation;

            public:
                Camera(const glm::vec3& position, const glm::quat& rotation, const glm::mat4& perspective);
                ~Camera();

                inline void setPosition(const glm::vec3& position) { _position = position; };
                inline glm::vec3 getPosition() const { return _position; };
                inline void move(const glm::vec3& delta) { _position += delta; }

                inline void setRotation(const glm::quat& rotation) { _rotation = rotation; }

                inline glm::mat4 getPerspective() const { return _perspective; }
                glm::mat4 getModelView() const;
            private:
            protected:
        };
    }
}


