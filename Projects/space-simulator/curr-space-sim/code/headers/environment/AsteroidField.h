#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <environment/Asteroid.h>
#include <graphics/renderers/BatchRenderer.h>
#include <actors/Pawn.h>
#include <cstdlib>

namespace sss {
    
    class AsteroidField {
        public:
            AsteroidField(const glm::vec3& position, const glm::vec3& little, const glm::vec3& large, int count, int size);
            ~AsteroidField();

            void submit(engine::graphics::BatchRenderer& renderer);
            void detect_collisions(engine::object::Pawn& object, bool isPlayer = false);
            void tick(float delta = 1.0f);
        private:
            std::vector<Asteroid*> _asteroids;
            void kill_asteroids();
        protected:
    };

}
