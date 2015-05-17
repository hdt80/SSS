#include <environment/Enemy.h>
#include <core/Game.h>

namespace sss {

    size_t Enemy::ID = 0;

    Enemy::Enemy(const glm::vec3& position, Parametric* course) :Super() {
        _id = ID++;
        if(course == nullptr) {

            // _course = new Parametric(6.28, 
            //         [](float theta, float phi) -> float{ return 10.0f  * (std::cosf(phi))*(std::sinf(theta)); },
            //         [](float theta, float phi) -> float{ return 10.0f  * (std::cosf(theta))*(std::sinf(phi)); },
            //         [](float theta, float phi) -> float{ return 10.0f * std::cosf(phi); });

            _course = new Parametric(6.283,
                    [](float theta, float phi) -> float{ return 600.0f * cosf(5.0f*phi) / 30.0f; }, // x function
                    [](float theta, float phi) -> float{ return 600.0f * sinf(4.0f*phi) / 30.0f; }, // y function
                    [](float theta, float phi) -> float{ return 600.0f * cosf(3.0f*phi) / 30.0f; }, // z function
                    0.01f);

        } else {
            _course = course;
        }

        _timer = new Timer(3000);
        
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
        delete _course;
        _course = nullptr;
        ID--;
    }

    void Enemy::onDestroy() {
        Super::onDestroy();
        std::stringstream ss;
        ss << "EVN#5;" << _id << ";";
        Connection::getInstance().write(ss.str());
    }

    void Enemy::tick(float delta) {
        movement(delta);
        if(canFire())
            fire();

        if(getCollider()->collides(SphereCollider(Game::getGame().getPlayer().getPosition(), 1))) {
            // TODO: what side we were hit on
            Connection::getInstance().write("EVN#1;0;");
            destroy();
        }
    }

    bool Enemy::canFire() {
        if(_timer->finished()) {
            _timer->restart();
            return glm::length(Game::getGame().getPlayer().getPosition() - getPosition()) < 100.0f;
        }
        return false;
    }

    void Enemy::fire(float delta) {
        Missile* m;
        glm::vec3 forward = glm::normalize(glm::mat3_cast(getRotation()) * glm::vec3(0, 0, 1));
        glm::vec3 position = getPosition() + 2.0f * forward;
        m = new Missile(position, 2.0f * forward);
        m->setRotation(getRotation());
        m->rotate(glm::vec3(1, 0, 0), 3.1415920f / 2.0f);
        Game::getGame().addMissile(m);
    }

    void Enemy::movement(float delta) {
        
        glm::vec3 next = glm::normalize(_course->next());
        glm::quat q = getRotation();
        glm::vec3 curr_forward = glm::normalize(glm::mat3_cast(q) * glm::vec3(0, 0, 1));
        glm::vec3 dp = glm::normalize(Game::getGame().getPlayer().getPosition() - getPosition());
        glm::vec3 cross = glm::cross(dp, curr_forward);
        float s = glm::length(cross);
        // printf("< %f, %f, %f > : ", dp.x, dp.y, dp.z);
        // printf("< %f, %f, %f > : ", next.x, next.y, next.z);
        // printf("< %f, %f, %f > : ", cross.x, cross.y, cross.z);
        // printf("< %f, %f, %f > : ", curr_forward.x, curr_forward.y, curr_forward.z);
        // printf("< %f, %f, %f, %f > : ", q.x, q.y, q.z, q.w);
        // printf("|| %f ||\n", s);

        if(s != 0.0f) // glm::rotate cuase nans to appear if the angle is 0.0f
            rotate(cross, s);
        
        move(next);
        // linear algebra in kinda cool, but mostly a pain in the ass
    }

} 
