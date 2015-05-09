#include <environment/Asteroid.h>
#include <core/Game.h>

namespace sss {

    Asteroid::Asteroid(const glm::vec3& position, float size)
        : This(position, size, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0))
    {
    } 

    Asteroid::Asteroid(const glm::vec3& position, float size, const glm::vec3& vector, const glm::vec3& rotAxis)
        : Super(), _initPos(position), _vector(vector), _rotAxis(rotAxis)
    {
        init(position, size);
    }

    Asteroid::~Asteroid() {
        delete _physics;
        delete _render;
        _physics = nullptr;
        _render = nullptr;


    }

    void Asteroid::init(const glm::vec3& position, float size) {
        static std::string array[3] = {
            "assets/models/asteroids/asteroid0.obj",
            "assets/models/asteroids/asteroid2.obj",
            "assets/models/asteroids/asteroid2.obj"
        };
        delete _input;
        delete _physics;
        _input = nullptr;
        setScale(glm::vec3(size, size, size));
        _physics = new engine::object::PhysicsComponent(new engine::physics::SphereCollider(position, size));
        _render = new engine::object::RenderComponent(array[rand() % 2], "assets/textures/asteroid1.png");
        setPosition(position);
    }

    void Asteroid::tick(float delta) {
        static const glm::vec3 NULL_VEC(0, 0, 0);
        if(_vector != NULL_VEC) {
            move(_vector);
            if(glm::length(getPosition() - _initPos) > 700.0f) {
                _vector *= -1.0f;
            }
        }
        if(_rotAxis != NULL_VEC)
            rotate(_rotAxis, glm::radians(1.0f));

        if(getCollider()->collides(SphereCollider(Game::getGame().getPlayer().getPosition(), 1))) {
            // TODO: what side we were hit on
            Connection::getInstance().write("EVN#1;0;");
            destroy();
        }

    } 

    void Asteroid::onSpawn() {
        _vector = glm::vec3((rand() % 4 - 2) / 100.0f, (rand() % 4 - 2) / 100.0f, (rand() % 4 - 2) / 100.0f);
        _rotAxis = glm::vec3(rand() % 2, rand() % 2, rand() % 2);
    }
}
