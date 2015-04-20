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
#include <core/Game.h>
#include <algorithm>

namespace sss {

    using engine::object::Actor;
    using engine::object::Pawn;
    using engine::graphics::Camera;
    using engine::graphics::Shader;
    using engine::graphics::BatchRenderer;
    using engine::physics::SphereCollider;
    using engine::Input;
    class Connection;
    using sss::Enemy;
    using sss::Missile;

    class Game {
        private:
            std::vector<Actor*> _children;
            std::vector<Missile*> _missiles;
            Camera _camera;
            Shader* _shader;
            Actor* _player; 
            BatchRenderer _renderer;
            bool _canFire;
        protected:
            Game(const Camera& camera);
            ~Game();
        public:
           
            static Game& getGame();

            void update(float delta=1.0f);
            void render();
            void sendMsg(const std::string& msg) {}
            inline void addChild(Actor* child) { _children.push_back(child); }  

            void addEnemy();
        private:
            void init();
            void player_stuff();
            void detect_collisions();
    };  
}
