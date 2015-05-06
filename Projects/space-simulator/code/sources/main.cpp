#define TESTING 0

#include <core/event_queue.h>

#if TESTING 


int main(int argc, char** argv) {

    sss_init_queue();

    sss_event events[4];
    for(int i = 0; i < 4; i++) 
        events[i].test_datum = i;
   
    sss_enque_event(events[0]);
    sss_enque_event(events[3]);
    sss_enque_event(events[2]);
    sss_enque_event(events[1]);

    sss_debug_queue();    

    sss_event t;
    while(sss_poll_event(&t)) 
        printf("%d\n", t.test_datum);
    

    return 0;
}






#else

#define GLM_FORCE_RADIANS
#include <graphics/Window.h>
#include <graphics/Shader.h>
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <graphics/renderers/BatchRenderer.h>
#include <environment/Asteroid.h>
#include <actors/Prop.h>
#include <input/Input.h>
#include <core/Game.h>
#include <thread>
#include <time.h>
#include <core/Connection.h>

static bool running = true;

void print_buffer() {
    while(running)
        sss::Connection::getInstance().printBuffer();
}

int main(int argc, char** agrv) {


    srand(time(NULL));
    using engine::graphics::Window;
    using engine::graphics::Shader;
    using engine::graphics::BatchRenderer;
    using engine::object::Prop;
    using engine::graphics::Camera;
    using engine::Input;

    using sss::Asteroid;
    using sss::Connection;

    Window window("sunset-space-simulator", 960, 540);
    std::cout << glGetString(GL_VERSION) << std::endl;
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
    glDepthMask(GL_TRUE);std::string file_path = "assets/shaders/textured";
    
    // Connection::getInstance().makeConnection("192.168.0.105", 5003);
    // Connection::getInstance().write("NAV");

    sss::Game::getGame();
    // std::thread method(print_buffer);
    // method.detach();
    while(not window.shouldClose()) {
        window.clear();



        sss::Game::getGame().update();
        sss::Game::getGame().render();

        if(Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
            break;
        }
        
        window.update();
    }
    // Connection::getInstance().disconnect();
    // exit(0);
    // running = false;

    
    return 0;
}

#endif

