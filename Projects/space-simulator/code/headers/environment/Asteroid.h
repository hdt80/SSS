#pragma once

#include <actors/Pawn.h>
#include <physics/SphereCollider.h>
#include <components/RenderComponent.h>
#include <cstdlib>
#include <cstdio>

namespace sss {
    
    class Asteroid : public engine::object::Pawn {
        private:
            typedef Pawn Super;
            typedef Asteroid This;

            const glm::vec3 _initPos;
            glm::vec3 _vector;
            glm::vec3 _rotAxis;

        public:
            Asteroid(const glm::vec3& position, float size);
            Asteroid(const glm::vec3& position, float size, const glm::vec3& vector, const glm::vec3& rotAxis);
            ~Asteroid();

            void tick(float delta=1.0f) override;
            void onSpawn() override;

            inline const glm::vec3& getVector() const { return _vector; }
            inline void setVector(const glm::vec3& vector) { _vector = vector; }

            inline const glm::vec3& getRotAxis() const { return _rotAxis; }
            inline void setRotAxis(const glm::vec3& rotAxis) { _rotAxis = rotAxis;  }
        private:
            void init(const glm::vec3& position, float size);

    };

}
