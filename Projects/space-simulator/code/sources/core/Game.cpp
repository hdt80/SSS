#include <core/Game.h>
#include <actors/Pawn.h>
#include <components/RenderComponent.h>
#include <core/Connection.h>

namespace sss {

    glm::vec3 getForward(const glm::quat& rot) {
        return glm::mat3_cast(rot) * glm::vec3(0, 0, 1);
    }

    glm::vec3 getRight(const glm::quat& rot) {
        return glm::mat3_cast(rot) * glm::vec3(1, 0, 0);
    }

    glm::vec3 getUp(const glm::quat& rot) {
        return glm::mat3_cast(rot) * glm::vec3(0, 1, 0);
    }
    
    Game::Game(const Camera& camera) 
        : _camera(camera)
    {
        _shader = new Shader("assets/shaders/textured.vs", "assets/shaders/textured.fs");
        _shader->bind();
        _player = new Player;
        _canFire = true;
        init();
    }

    Game& Game::getGame() {
        static Game game(Camera(glm::vec3(0, 0, 0), glm::quat(0, 0, 0, 1), 
                    glm::perspective(glm::radians(70.0f), 960.0f / 540.0f, 0.1f, 1000.0f)));
        return game;
    }


    Game::~Game() {
        _shader->unbind();
        delete _shader;
        delete _player;
        _shader = nullptr;
        _player = nullptr;
        for(size_t i = 0; i < _children.size(); i++)
            delete _children[i];
        _children.clear();
    }

    void Game::update(float delta) {
        _player->tick(delta);
        detect_collisions();
        _camera.setPosition(_player->getPosition());
        _camera.setRotation(_player->getRotation());

        _shader->setUniformMat4("perspective", _camera.getModelView());

        for(size_t i = 0; i < _children.size(); i++) {
            if(_children[i]->isPendingKill()) {
                delete _children[i];
                _children[i] = nullptr;
            } else {
                _children[i]->tick();
            }
        }

        for(size_t i = 0; i < _missiles.size(); i++) {
            if(_missiles[i]->isPendingKill()) {
                delete _missiles[i];
                _missiles[i] = nullptr;
            } else {
                _missiles[i]->tick();
            }
        }

        auto iter(std::remove_if(_children.begin(), _children.end(), [](Actor* a) -> bool { return a == nullptr; }));
        _children.erase(iter, _children.end());
        _children.shrink_to_fit();

        auto iter2(std::remove_if(_missiles.begin(), _missiles.end(), [](Missile* m) -> bool {return m == nullptr; }));
        _missiles.erase(iter2, _missiles.end());
        _missiles.shrink_to_fit();
    }

    void Game::render() {
        _renderer.begin();

        for(const auto& c : _children)
            _renderer.submit(c);

        for(const auto& m : _missiles)
            _renderer.submit(m);

        _renderer.end();
        _renderer.flush();
    }

    void Game::addEnemy() {
        _children.push_back(new Enemy(glm::vec3(rand() % 100, rand() % 100, rand() % 100), nullptr));
    }

    void Game::init() {
        int texts[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        _shader->setUniform1iv("textures", texts, 16);
        for(size_t i = 0; i < 200; i++) {
            Asteroid* a = new Asteroid(glm::vec3(rand() % 600 - 300, rand() % 600 - 300, rand() % 600 - 300), 3);
            a->setScale(glm::vec3(3, 3, 3));
            a->onSpawn();
            _children.push_back(a);
        }

        _children.push_back(new Enemy(glm::vec3(20, 20, 20), nullptr));
        _children.push_back(new Enemy(glm::vec3(80, 80, 80), nullptr));
    }

    void Game::detect_collisions() {
        for(auto& c : _children) {

            Pawn* p = dynamic_cast<Pawn*>(c);
            if(p == nullptr)
                continue;
            if(p->getCollider()->collides(SphereCollider(_player->getPosition(), 1))) {
                p->destroy();
                Connection::getInstance().write("EVN#0;9;");
            }

            for(auto& m : _missiles) {
                if(p->getCollider()->collides(*m->getCollider())) {
                    m->destroy();
                    p->destroy();
                }

                if(glm::length(m->getPosition() - _player->getPosition()) > 300.0f)
                    m->destroy();

                // send missle hit

            }

        }

    }
}
