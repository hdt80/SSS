#include <core/Game.h>
#include <actors/Pawn.h>
#include <components/RenderComponent.h>
#include <core/Connection.h>

namespace sss {

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
        delete _asteroidField;
        _shader = nullptr;
        _player = nullptr;
        _asteroidField = nullptr;
        for(size_t i = 0; i < _children.size(); i++)
            delete _children[i];
        _children.clear();
    }

    void Game::update(float delta) {
        _player->tick(delta);
        _asteroidField->tick(delta);
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

        /* both these iterators go through and free the memory of 
         * missiles, asteroids, and enemies no longer in use 
         */
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
        
        _asteroidField->submit(_renderer);

        _renderer.end();
        _renderer.flush();
    }

    void Game::addEnemy() {
        _children.push_back(new Enemy(glm::vec3(rand() % 100, rand() % 100, rand() % 100), nullptr));
    }

    void Game::init() {
        int texts[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        _shader->setUniform1iv("textures", texts, 16);
        _asteroidField = new AsteroidField(glm::vec3(0, 0, 0), glm::vec3(450, 450, 450), glm::vec3(900, 900, 900), 200, 3);
        _children.push_back(new Enemy(glm::vec3(0, 0, -30), nullptr));
    }

    /* abstract into things*/
    void Game::detect_collisions() {
        _asteroidField->detect_collisions(*_player, true);
        
        /* enemy missles attacking us */
        for(auto& m : _missiles) {
            if(m->getCollider()->collides(*_player->getCollider())) {
                m->destroy();
                Connection::getInstance().write("EVN#5;0;");
            }
        }
        
        /* add our missles hit something */

    }
}
