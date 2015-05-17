#include <core/EventHandler.h>
#include <core/Game.h>
#include <environment/Enemy.h>
#include <glm/glm.hpp>
#include <environment/Missile.h>
#include <cstdlib>

namespace sss {
    void EventHandler::handle_event(const sss_event& evnt) {
        switch(evnt.type) {
            case EVN:
                handle_evn_event(evnt);
                break;
            case SET:
                handle_set_event(evnt);
                break;
            case GET:
                handle_get_event(evnt);
                break;
            case ERR:
                std::cout << "We dun git en error" << std::endl;
                break;
            default:
                // print error
                break;
        };
    }

    void EventHandler::handle_set_event(const sss_event& evnt) {
    
    }

    void EventHandler::handle_get_event(const sss_event& evnt) {
    
    }

    void EventHandler::handle_evn_event(const sss_event& evnt) {
        switch(evnt.evn) {
            case SPWANENEMY:
                std::cout << "adding an enemy: " << evnt.evn << std::endl;
                // for(int i = 0; i < evnt.args[1] + 1; i++) {
                for(int i = 0; i < 1; i++) {
                    Enemy* enemy = new Enemy(Game::getGame().getPlayer().getPosition() + glm::vec3(rand() % 300 - 150,
                                                                                                   rand() % 300 - 150,
                                                                                                   rand() % 300 - 150), nullptr);
                    Game::getGame().addSpawn(enemy); 
                } 
                std::cout << "added the enemy" << std::endl;
                break;
            case COLLISION:
                break;
            case WE_FIRE:
                {
                    Missile* m = nullptr;
                    glm::vec3 player_forward = glm::normalize(glm::mat3_cast(Game::getGame().getPlayer().getRotation()) * glm::vec3(0, 0, 1));
                    glm::vec3 m_pos = Game::getGame().getPlayer().getPosition() - 8.0f * player_forward;
                    m = new Missile(m_pos, -2.0f * player_forward);
                    m->setRotation(Game::getGame().getPlayer().getRotation());
                    m->rotate(glm::vec3(-1, 0, 0), 3.14/2);
                    Game::getGame().addMissile(m);
                }
                break;
            case MINI_GAME_DONE:
                break;
            case POWER_CHANGE:
                break;
            case ENEMY_DESPAWN:
                break;
            case CHANGE_MAX_POWER:
                break;
            default:
                // print error
                break;
        };
    }
}
