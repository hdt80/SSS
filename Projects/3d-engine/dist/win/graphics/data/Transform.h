#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

namespace engine {
    namespace graphics {
        
        class Transform {
            private:
                glm::vec3 _position;
                glm::vec3 _scale;
                glm::quat _rotation;

            public:

                Transform(const glm::vec3& position=glm::vec3(0, 0, 0), 
                          const glm::quat& rotation=glm::quat(0, 0, 0, 1), 
                          const glm::vec3& scale=glm::vec3(1, 1, 1));

                /* Standard setters and getters for private data members */
                inline void setPosition(const glm::vec3& position) { _position = position; }
                inline const glm::vec3& getPosition() const { return _position; }

                inline void setScale(const glm::vec3& scale) {  _scale = scale; }
                inline const glm::vec3& getScale() const { return _scale; }

                inline void setRotation(const glm::quat& rotation) { _rotation = rotation; }
                inline const glm::quat& getRotation() const { return _rotation; }


                /* Setters and Getters for components of position and scale */
                inline void setPositionX(float x) { _position.x = x; }
                inline void setPositionY(float y) { _position.y = y; }
                inline void setPositionZ(float z) { _position.z = z; }

                inline float getPositionX() const { return _position.x; }
                inline float getPositionY() const { return _position.y; }
                inline float getPositionZ() const { return _position.z; }

                inline void setScaleX(float x) { _scale.x = x; }
                inline void setScaleY(float y) { _scale.y = y; }
                inline void setScaleZ(float z) { _scale.z = z; }

                /* rotate this transformation about a given axis and a given angle */
                void rotate(const glm::vec3& axis, float theta);

                /* move this transformation */
                void translate(const glm::vec3& delta);

                /* various transformation functions */
                glm::mat4 getTranslationMatrix() const;
                glm::mat4 getScaleMatrix() const;
                glm::mat4 getRotationMatrix() const;

                glm::mat4 getTransformation() const;
            private:
            protected:

        };

    }
}
