#include <environment/AsteroidField.h>

namespace sss {

    AsteroidField::AsteroidField(const glm::vec3& little, const glm::vec3& large, int count, int size) {
        glm::vec3 len = large - little; 
        for(int i = 0; i < count; i++) {
            Asteroid* a = new Asteroid(glm::vec3(rand() % (int)(large.x - len.x), 
                                                 rand() % (int)(large.y - len.y), 
                                                 rand() % (int)(large.z - len.z)), size);
            a->setScale(glm::vec3(size, size, size));
            a->onSpawn();
            _asteroids.push_back(a);
        }
    }

    AsteroidField::~AsteroidField() {
        for(size_t i = 0; i < _asteroids.size(); i++) {
            delete _asteroids[i];
            _asteroids[i] = nullptr;
        }
        _asteroids.clear();
    }

    void AsteroidField::submit(engine::graphics::BatchRenderer& renderer) {
        for(auto& a : _asteroids) 
            renderer.submit(a);
    }

    void AsteroidField::detect_collisions(engine::object::Pawn& object, bool isPlayer) {
        // TODO: implement
    }

    void AsteroidField::tick(float delta) {
        for(size_t i = 0; i < _asteroids.size(); i++) {
            if(_asteroids[i]->isPendingKill()) {
                delete _asteroids[i];
                _asteroids[i] = nullptr;
            } else {
                _asteroids[i]->tick(delta);
            }
        }
        kill_asteroids();
    }

    void AsteroidField::kill_asteroids() {

        auto iter(std::remove_if(_asteroids.begin(), _asteroids.end(), [](Asteroid* a) -> bool { return a == nullptr; }));
        _asteroids.erase(iter, _asteroids.end());
        _asteroids.shrink_to_fit();

    }

}
