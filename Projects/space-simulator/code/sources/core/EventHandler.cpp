#include <core/EventHandler.h>
#include <core/Game.h>
#include <environment/Enemy.h>
#include <glm/glm.hpp>
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
            case ERROR:
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
                std::cout << "adding an enemy" << std::endl;
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
