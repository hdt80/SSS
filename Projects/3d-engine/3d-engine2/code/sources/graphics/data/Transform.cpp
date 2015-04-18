#include <graphics/data/Transform.h>

namespace engine {
    namespace graphics {
        
        Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
            : _position(position), _scale(scale), _rotation(rotation)
        {
            
        }

        void Transform::rotate(const glm::vec3& axis, float theta) {
            _rotation = glm::rotate(_rotation, theta, axis); 
        }

        void Transform::translate(const glm::vec3& delta) {
            _position += delta; 
        }

        glm::mat4 Transform::getTranslationMatrix() const {
            return glm::translate(_position);
        }

        glm::mat4 Transform::getScaleMatrix() const {
            return glm::scale(_scale);
        }

        glm::mat4 Transform::getRotationMatrix() const {
            return glm::mat4_cast(_rotation);
        }

        glm::mat4 Transform::getTransformation() const {
            glm::mat4 trans = getTranslationMatrix();
            glm::mat4 scale = getScaleMatrix();
            glm::mat4 rot   = getRotationMatrix();

            return trans * rot * scale;
        }

    }
}
