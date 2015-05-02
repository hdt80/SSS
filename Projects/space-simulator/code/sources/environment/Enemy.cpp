#include <environment/Enemy.h>

namespace sss {
    

    Enemy::Enemy(const glm::vec3& position, Parametric* course) :Super() {
       
        if(course == nullptr) {
            
            // _course = new Parametric(6.28, 
            //         [](float theta, float phi) -> float{ return 10.0f  * (std::cosf(phi))*(std::sinf(theta)); },
            //         [](float theta, float phi) -> float{ return 10.0f  * (std::cosf(theta))*(std::sinf(phi)); },
            //         [](float theta, float phi) -> float{ return 10.0f * std::cosf(phi); });
            
            _course = new Parametric(6.283,
                    [](float theta, float phi) -> float{ return 600.0f * cosf(5.0f*phi) / 30.0f; },
                    [](float theta, float phi) -> float{ return 600.0f * sinf(4.0f*phi) / 30.0f; },
                    [](float theta, float phi) -> float{ return 600.0f * cosf(3.0f*phi) / 30.0f; },
                    0.01f);
        
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
        glm::vec3 next = glm::normalize(_course->next());
        glm::vec3 curr_forward = glm::normalize(glm::mat3_cast(getRotation()) * glm::vec3(0, 0, 1));
        glm::vec3 cross = glm::cross(next, curr_forward);
        rotate(cross, asinf(glm::length(cross)));
        move(next);
    }

} 
