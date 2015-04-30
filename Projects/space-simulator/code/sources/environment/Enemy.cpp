#include <environment/Enemy.h>

namespace sss {
    

    Enemy::Enemy(const glm::vec3& position, Parametric* course) :Super() {
       
        if(course == nullptr) {
            
            // _course = new Parametric(6.28, 
            //         [](float theta, float phi) -> float{ return 10.0f  * (std::cosf(phi))*(std::sinf(theta)); },
            //         [](float theta, float phi) -> float{ return 10.0f  * (std::cosf(theta))*(std::sinf(phi)); },
            //         [](float theta, float phi) -> float{ return 10.0f * std::cosf(phi); });
            
            _course = new Parametric(6.28,
                    [](float theta, float phi) -> float{ return 600.0f * std::cosf(5.0f*phi) / 30.0f; },
                    [](float theta, float phi) -> float{ return 600.0f * std::sinf(4.0f*phi) / 30.0f; },
                    [](float theta, float phi) -> float{ return 600.0f * std::cosf(3.0f*phi) / 30.0f; });
        
        } else {
            _course = course;
        }

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
        move(glm::normalize(_course->next())); 
    }

} 
