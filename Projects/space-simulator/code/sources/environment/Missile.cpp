#include <environment/Missile.h>
#include <core/Game.h>

namespace sss {
    

    Missile::Missile(const glm::vec3& position, const glm::vec3& vector) 
        : Super()
    {
        delete _input;
        delete _physics;

        if(glm::length(vector) > 1) 
            _vector = glm::normalize(vector);
        else
            _vector = vector;

        _input   = nullptr;
        _physics = new engine::object::PhysicsComponent(new engine::physics::SphereCollider(position, 1.25));
        _render  = new engine::object::RenderComponent("assets/models/missile.obj", "assets/textures/missile2.png");

        setPosition(position);
    }

    Missile::~Missile() {
        delete _physics;
        delete _render;

        _physics = nullptr;
        _render  = nullptr;
    }
    
    void Missile::tick(float delta) {
        move(_vector);

        if(glm::length(getPosition() - Game::getGame().getPlayer().getPosition()) > 200.0f)
            destroy();
    } 
}
