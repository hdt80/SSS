#pragma once

#include <actors/Actor.h>
#include <graphics/Camera.h>
#include <graphics/Shader.h>
#include <environment/Asteroid.h>
#include <graphics/renderers/BatchRenderer.h>
#include <vector>
#include <actors/Pawn.h>
#include <input/Input.h>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

namespace sss {

    using engine::object::Actor;
    using engine::object::Pawn;
    using engine::graphics::Camera;
    using engine::graphics::Shader;
    using engine::graphics::BatchRenderer;
    using engine::physics::SphereCollider;
    using engine::Input;

    class Game {
        private:
            std::vector<Actor*> _children;
            Camera _camera;
            Shader* _shader;
            Actor* _player; 
            BatchRenderer _renderer;
        public:
            Game(const Camera& camera);
            ~Game();
            
            void update(float delta=1.0f);
            void render();
            void sendMsg(const std::string& msg) {}
            inline void addChild(Actor* child) { _children.push_back(child); }  

        private:
            void init();
            void player_stuff();
            void detect_collisions();
    };  
}
