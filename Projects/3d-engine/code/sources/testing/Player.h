#pragma once

#include <actors/Pawn.h>
#include <unordered_map>

namespace engine {
    namespace object {
        class Player;
        
        class Player : public Pawn {
            private:
                typedef Pawn Super;
                typedef Player This;

            public:
                Player(const glm::vec3& position, float size);
                ~Player();

                void tick(float delta=1.0f) override;
               
            // protected:
                void move_left();
                void move_right();
                void move_up();
                void move_down();
                void rotate_left();
                void rotate_right();
            private:
                void bindKeys() override;
        };

        class PlayerInput : public InputComponent {
            protected:
                std::unordered_map<unsigned int, std::function<void(Player&)>> _commands;
            public:
                PlayerInput() {}

                ~PlayerInput() {}

                void bind(unsigned int key, Player& actor, void(Player::*arg)()) {
                    if(_commands.count(key))
                        return;
                    _commands[key] = arg;
                    //std::bind(arg, actor);
                }

                void execute(Player& actor, float delta=1.0f) {
                    for(auto& pair : _commands) 
                        if(Input::isKeyPressed(pair.first))
                            pair.second(actor);
                }

                void update(Actor&, float) override {}
        };

    }
}

