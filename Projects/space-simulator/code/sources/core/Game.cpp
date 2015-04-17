#include <core/Game.h>

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
            : _camera(camera) {
        _shader = new Shader("assets/shaders/textured.vs", "assets/shaders/textured.fs");
        _shader->bind();
        _player = new Actor;
        init();
    }

    Game::~Game() {
        _shader->unbind();

        delete _shader;
        delete _player;

        _shader = nullptr;
        _player = nullptr;

        for(int i = 0; i < _children.size(); i++) {
            delete _children[i];
        }
        
        _children.clear();
    }

    void Game::update(float delta) {
        player_stuff();
        detect_collisions();
        _camera.setPosition(_player->getPosition());
        _camera.setRotation(_player->getRotation());
        
        _shader->setUniformMat4("perspective", _camera.getModelView());
        
        for(int i = 0; i < _children.size(); i++) {
            if(_children[i]->isPendingKill()) {
                delete _children[i];
                _children[i] = nullptr;
            } else {
                _children[i]->tick();
            }
        }
        auto iter(std::remove_if(_children.begin(), _children.end(), [](Actor* a) -> bool { return a == nullptr; }));
        _children.erase(iter, _children.end());
        _children.shrink_to_fit();
    }

    void Game::render() {
        _renderer.begin();

        for(const auto& c : _children)
            _renderer.submit(c);

        _renderer.end();
        _renderer.flush();
    }

    /* handle player input */
    void Game::player_stuff() {
        static glm::vec3 Y_AXIS(0, 1, 0);
        static glm::vec3 X_AXIS(1, 0, 0);
        static glm::vec3 Z_AXIS(0, 0, 1);

        /*  looking around */
        if(Input::isKeyPressed(GLFW_KEY_J)) {
            _player->rotate(Y_AXIS, 0.01);
        } else if(Input::isKeyPressed(GLFW_KEY_L)) {
            _player->rotate(Y_AXIS, -0.01);
        }

        if(Input::isKeyPressed(GLFW_KEY_I)) {
            _player->rotate(X_AXIS, 0.01);
        } else if(Input::isKeyPressed(GLFW_KEY_K)) {
            _player->rotate(X_AXIS, -0.01);
        }

	   if(Input::isKeyPressed(GLFW_KEY_U))
	_player->rotate(Z_AXIS, 0.01);
	else if(Input::isKeyPressed(GLFW_KEY_O))
	    _player->rotate(Z_AXIS, -0.01);

        glm::vec3 forward = getForward(_player->getRotation());
        glm::vec3 right   = getRight(_player->getRotation());
        /* movement */
        if(Input::isKeyPressed(GLFW_KEY_W))
            _player->move(-0.1f * forward);
        else if(Input::isKeyPressed(GLFW_KEY_S))
            _player->move(0.1f * forward);
        
        if(Input::isKeyPressed(GLFW_KEY_D))
            _player->move(0.1f * right);
        else if(Input::isKeyPressed(GLFW_KEY_A))
            _player->move(-0.1f * right);

    }

    void Game::init() {
        int texts[16] = {0};
        _shader->setUniform1iv("textures", texts, 16);
        for(unsigned long long i = 0; i < 20; i++) {
            Asteroid* a = new Asteroid(glm::vec3(rand() % 200 - 100, rand() % 200 - 100, rand() % 200 - 100), 1);
            a->onSpawn();
            _children.push_back(a);
        }
        _children[0]->destroy();
    }

    void Game::detect_collisions() {
        for(auto& c : _children) {
            Pawn* p = dynamic_cast<Pawn*>(c);
            if(p == nullptr)
                continue;
            if(p->getCollider()->collides(SphereCollider(_player->getPosition(), 1))) {
                p->destroy();
                std::cout << "Send To Server Asteroid Struck" << std::endl;
            }
        } 
    }
}
