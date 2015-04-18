#include <core/Game.h>
#include <actors/Pawn.h>
#include <components/RenderComponent.h>

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
        _player = new Actor;
        _canFire = true;
        init();
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
        Connection::getInstance().printBuffer();
        player_stuff();
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

    /* handle player input */
    void Game::player_stuff() {
        static glm::vec3 Z_AXIS(0, 0, 1);
        static glm::vec3 Y_AXIS(0, 1, 0);
        static glm::vec3 X_AXIS(1, 0, 0);

        /*  looking around */
        if(Input::isKeyPressed(GLFW_KEY_J)) 
            _player->rotate(Y_AXIS, 2);
        else if(Input::isKeyPressed(GLFW_KEY_L)) 
            _player->rotate(Y_AXIS, -2);

        if(Input::isKeyPressed(GLFW_KEY_I))
            _player->rotate(X_AXIS, 0.1);
        else if(Input::isKeyPressed(GLFW_KEY_K))
            _player->rotate(X_AXIS, -0.1);

        if(Input::isKeyPressed(GLFW_KEY_U))
            _player->rotate(Z_AXIS, 0.1);
        else if(Input::isKeyPressed(GLFW_KEY_O))
            _player->rotate(Z_AXIS, -0.1);

        glm::vec3 forward = getForward(_player->getRotation());
        glm::vec3 right   = getRight(_player->getRotation());
        /* movement */
        if(Input::isKeyPressed(GLFW_KEY_W))
            _player->move(-0.01f * forward);
        else if(Input::isKeyPressed(GLFW_KEY_S))
            _player->move(0.01f * forward);

        if(Input::isKeyPressed(GLFW_KEY_D))
            _player->move(0.01f * right);
        else if(Input::isKeyPressed(GLFW_KEY_A))
            _player->move(-0.01f * right);

        /* firing */
        if(_canFire and Input::isKeyPressed(GLFW_KEY_F)) {
            glm::vec3 position = _player->getPosition() + glm::vec3(0, 0, -5) * forward;
            Missile* m = new Missile(position, -0.4f * forward);
            m->setRotation(_player->getRotation());
            m->rotate(glm::vec3(1, 0, 0), -90);
            _missiles.push_back(m);
            _canFire = false;
        } else if(not _canFire and not Input::isKeyPressed(GLFW_KEY_F)) {
            _canFire = true; 
        }

    }

    void Game::init() {
        int texts[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        _shader->setUniform1iv("textures", texts, 16);
        for(size_t i = 0; i < 400; i++) {
            Asteroid* a = new Asteroid(glm::vec3(rand() % 300 - 150, rand() % 300 - 150, rand() % 300 - 150), 1);
            a->onSpawn();
            _children.push_back(a);
        }

        _children.push_back(new Enemy(glm::vec3(20, 20, 20), glm::vec3(0, 0, 0)));
        _children.push_back(new Enemy(glm::vec3(80, 80, 80), glm::vec3(54, 54, 54)));


        _missiles.push_back(new Missile(glm::vec3(-1, -1, -1), glm::vec3(0, 0, 0)));
        // _children[0]->destroy();
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

                if(glm::length(m->getPosition() - _player->getPosition()) > 700.0f)
                    m->destroy();

                // send missle hit

            }

        }

    }
}
