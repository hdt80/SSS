#include <core/Player.h>

namespace sss {

    Player::Player(const glm::vec3& position) : Super() {
        delete _input;
        delete _physics;
        delete _render;

        _input   = nullptr;
        _physics = nullptr;
        _render  = nullptr;

        _physics = new engine::object::PhysicsComponent(new engine::physics::SphereCollider(position, 1.5f));
        _input   = new PlayerInput();

        for(int i = 0; i < NUM_POWER_COMPS; i++)
            _power[i] = 0.0f;

        _power[SHIELD_POWER] = 100.0f;

        setPosition(position);
    }

    Player::~Player() {
        delete _physics;
        _physics = nullptr;
    }

    void Player::tick(float delta) {
        _input->update(*this, delta); 
    }

    void Player::onSpawn() {
        // dont do anything 
    }

    void Player::onDestroy() {
    
    }

    void Player::handleEvent(const sss_event& evt) {

    }


    /***********************************
     * PlayerInput
     **********************************/
    PlayerInput::PlayerInput() : Super() {

    }

    PlayerInput::~PlayerInput() {

    }

    void PlayerInput::update(Actor& actor, float delta) {
        static glm::vec3 Z_AXIS(0, 0, 1);
        static glm::vec3 Y_AXIS(0, 1, 0);
        static glm::vec3 X_AXIS(1, 0, 0);

        glm::vec3 forward = glm::mat3_cast(actor.getRotation()) * Z_AXIS;
        glm::vec3 right   = glm::mat3_cast(actor.getRotation()) * X_AXIS;
        /* Motion */
        if(Input::isKeyPressed(GLFW_KEY_W))
            actor.move(-0.1f * forward);
        else if(Input::isKeyPressed(GLFW_KEY_S))
            actor.move(0.1f * forward);

        if(Input::isKeyPressed(GLFW_KEY_D))
            actor.move(0.1f * right);
        else if(Input::isKeyPressed(GLFW_KEY_A))
            actor.move(-0.1f * right);

        /* Looking */
        if(Input::isKeyPressed(GLFW_KEY_J)) 
            actor.rotate(Y_AXIS, glm::radians(2.0f));
        else if(Input::isKeyPressed(GLFW_KEY_L)) 
            actor.rotate(Y_AXIS, glm::radians(-2.0f));

        if(Input::isKeyPressed(GLFW_KEY_I))
            actor.rotate(X_AXIS, glm::radians(2.0f));
        else if(Input::isKeyPressed(GLFW_KEY_K))
            actor.rotate(X_AXIS, glm::radians(-2.0f));

        if(Input::isKeyPressed(GLFW_KEY_U))
            actor.rotate(Z_AXIS, glm::radians(2.0f));
        else if(Input::isKeyPressed(GLFW_KEY_O))
            actor.rotate(Z_AXIS, glm::radians(-2.0f));

    }
}
