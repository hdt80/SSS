#include <environment/Enemy.h>

namespace sss {
    

    Enemy::Enemy(const glm::vec3& position, const glm::vec3& rotPoint) :Super() {
        _radius = glm::length(rotPoint - position);
        delete _input;
        delete _physics;

        _physics = nullptr;
        _input = nullptr;

        _render  = new engine::object::RenderComponent("assets/models/enemy_ship.obj", "assets/textures/color.png");
        _physics = new engine::object::PhysicsComponent(new engine::physics::SphereCollider(position, 1.5f));

        setPosition(position);
    }

    Enemy::~Enemy() {
        delete _render;
        _render = nullptr;
    }

    void Enemy::tick(float delta) {
        static float s = std::sinf(0.01);
        static float c = std::cosf(0.01);

        float px = getPosition().x - _rotPoint.x;
        float py = getPosition().z - _rotPoint.y;

        float newx = px * c - py * s;
        float newy = px * s + py * c;

        setPosition(glm::vec3(newx + _rotPoint.x, getPosition().y, newy + _rotPoint.z));

    }

} 
