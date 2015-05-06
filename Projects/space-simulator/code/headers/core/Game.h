#pragma once

#include <actors/Actor.h>
#include <graphics/Camera.h>
#include <graphics/Shader.h>
#include <environment/Asteroid.h>
#include <graphics/renderers/BatchRenderer.h>
#include <vector>
#include <actors/Pawn.h>
#include <input/Input.h>
#include <environment/Enemy.h>
#include <environment/Missile.h>
#include <core/Connection.h>
#include <glm/glm.hpp>
#include <algorithm>
#include <core/Player.h>

namespace sss {

    using engine::object::Actor;
    using engine::object::Pawn;
    using engine::graphics::Camera;
    using engine::graphics::Shader;
    using engine::graphics::BatchRenderer;
    using engine::physics::SphereCollider;
    using engine::Input;
    using sss::Enemy;
    using sss::Missile;

    class Connection;
    class Game {
        private:
            std::vector<Actor*> _children;
            std::vector<Missile*> _missiles;
            Camera _camera;
            Shader* _shader;
            Player* _player; 
            BatchRenderer _renderer;
            bool _canFire;
        protected:
            Game(const Camera& camera);
            ~Game();
        public:
           
            static Game& getGame();

            void update(float delta=1.0f);
            void render();

            /* Adds an either an asteroid or an enemy to the world */
            inline void addSpawn(Actor* child) { _children.push_back(child); }
            /* Create an enemy and add it to the world */
            void addEnemy();
            /* Adds an emeny to the world */
            inline void addMissile(Missile* missile) { _missiles.push_back(missile); }
           
            /* returns the games player */
            inline const Player& getPlayer() const { return *_player; }

        private:
            void init();
            void detect_collisions();
    };  
}
