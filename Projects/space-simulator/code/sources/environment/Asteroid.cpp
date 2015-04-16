#include <environment/Asteroid.h>

namespace sss {
    
    Asteroid::Asteroid(const glm::vec3& position, float size)
        : This(position, size, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0))
    {
    } 

    Asteroid::Asteroid(const glm::vec3& position, float size, const glm::vec3& vector, const glm::vec3& rotAxis)
        : Super(), _vector(vector), _rotAxis(rotAxis)
    {
        init(position, size);
    }

    Asteroid::~Asteroid() {
        delete _physics;
        delete _render;
        _physics = nullptr;
        _render = nullptr;

       // std::cout << "Yo" << std::endl;

    }

    void Asteroid::init(const glm::vec3& position, float size) {
        delete _input;
        delete _physics;
        _input = nullptr;
        _physics = new engine::object::PhysicsComponent(new engine::physics::SphereCollider(position, size));
        _render = new engine::object::RenderComponent("assets/models/asteroid0.obj", "assets/textures/asteroid1.png");
        setPosition(position);
    }

    void Asteroid::tick(float delta) {
        static const glm::vec3 NULL_VEC(0, 0, 0);
        if(_vector != NULL_VEC)
            move(_vector);
        if(_rotAxis != NULL_VEC)
            rotate(_rotAxis, 0.01f);
    } 

    void Asteroid::onSpawn() {
        _vector = glm::vec3((rand() % 4 - 2) / 100.0f, (rand() % 4 - 2) / 100.0f, (rand() % 4 - 2) / 100.0f);
        _rotAxis = glm::vec3(rand() % 2, rand() % 2, rand() % 2);
    }
}
