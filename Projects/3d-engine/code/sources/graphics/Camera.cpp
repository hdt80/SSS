#include <graphics/Camera.h>

namespace engine {
    namespace graphics {
        Camera::Camera(const glm::vec3& position, const glm::quat& rotation, const glm::mat4& perspective) {
            _perspective = perspective;
            _position = position;
            _rotation = rotation;
        }

        Camera::~Camera() {

        }

        glm::mat4 Camera::getModelView() const {
            return _perspective * glm::mat4_cast(glm::conjugate(_rotation)) * glm::translate(_position * -1.0f); 
        }
    }
}
