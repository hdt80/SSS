#include "Player.h"
#include <physics/SphereCollider.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <graphics/data/Vertex.h>
#include <utils/MeshUtils.h>
#include <components/RenderComponent.h>

namespace engine {
    namespace object {

        Player::Player(const glm::vec3& position, float size) : Super() {
            delete _input;
            delete _physics;
            _input = new PlayerInput;
            _physics = new PhysicsComponent(new physics::SphereCollider(position, size));
            bindKeys();
            
            _render = new RenderComponent("assets/models/box.obj", "assets/textures/color.png");
            setPosition(position);

        } 

        Player::~Player() {
            delete _render;
            delete _input;
            delete _physics;

            _render = nullptr;
            _input = nullptr;
            _physics = nullptr;
        }

        void Player::tick(float delta) {
            static_cast<PlayerInput*>(_input)->execute(*this, delta); 
        }

        void Player::bindKeys() {
            static_cast<PlayerInput*>(_input)->bind(GLFW_KEY_W, *this, &This::move_up);
            static_cast<PlayerInput*>(_input)->bind(GLFW_KEY_S, *this, &This::move_down);
            static_cast<PlayerInput*>(_input)->bind(GLFW_KEY_D, *this, &This::move_right);
            static_cast<PlayerInput*>(_input)->bind(GLFW_KEY_A, *this, &This::move_left);
            static_cast<PlayerInput*>(_input)->bind(GLFW_KEY_Q, *this, &This::rotate_right);
            static_cast<PlayerInput*>(_input)->bind(GLFW_KEY_E, *this, &This::rotate_left);
        }

        void Player::move_left() {
            move(glm::vec3(-0.1, 0, 0)); 
        }

        void Player::move_right() {
            move(glm::vec3(0.1, 0, 0));
        }

        void Player::move_up() {
            move(glm::vec3(0, 0.1, 0));
        }

        void Player::move_down() {
            move(glm::vec3(0, -0.1, 0));
        }

        void Player::rotate_left() {
            rotate(glm::vec3(0, 0, 1), 10);
        }

        void Player::rotate_right() {
            rotate(glm::vec3(0, 0, 1), -10);
        }

    }
}
