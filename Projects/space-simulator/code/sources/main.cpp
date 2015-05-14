#define TESTING 1

#include <core/event_queue.h>

#if TESTING 


int main(int argc, char** argv) {

    sss_init_queue();

    sss_event events[4];
    for(int i = 0; i < 4; i++) 
        events[i].args[0] = i;

    sss_enque_event(sss_parse_event("EVN#0;1;2;3;4;5;@"));
    // sss_enque_event(sss_parse_event("EVN#0;1;2;3;4;5;@\0"));
    // sss_enque_event(sss_parse_event("EVN#0;1;2;3;4;5;@\0"));
    // sss_enque_event(sss_parse_event("EVN#0;1;2;3;4;5;@\0"));

    sss_debug_queue();    

    sss_event t;
    while(sss_poll_event(&t)) 
        printf("%d\n", t.evn);




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
    puts("talking to the server");
    while(running)
        sss::Connection::getInstance().printBuffer();
}

int main(int argc, char** argv) {

    const char* firstArg = argc >= 2 ? argv[1] : "NULL\0";

    srand(time(NULL));
    using engine::graphics::Window;
    using engine::graphics::Shader;
    using engine::graphics::BatchRenderer;
    using engine::object::Prop;
    using engine::graphics::Camera;
    using engine::Input;
    using sss::Asteroid;
    using sss::Connection;

    Window window("sunset-space-simulator", 960, 540, false);
    window.showMouse(false);
    std::cout << glGetString(GL_VERSION) << std::endl;
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
    glDepthMask(GL_TRUE);

    bool connectToServer = strcmp(firstArg, "NULL");

    /* only do server connect if args are present */
    if(connectToServer) {
        Connection::getInstance().makeConnection("127.0.0.1", 5003);
        Connection::getInstance().write("NAV");
    }

    sss::Game::getGame();

#ifdef __APPLE__
    /* only start the thread if on apple, and args are specifed */
    if(connectToServer) {
        std::thread method(print_buffer);
        method.detach();
    }
#endif

    while(not window.shouldClose()) {
        window.clear();

        sss::Game::getGame().update();
        sss::Game::getGame().render();

        if(Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
            break;
        }

        window.update();
    }

    window.showMouse(true);
    if(connectToServer)
        Connection::getInstance().disconnect();
    running = false;


    return 0;
}

#endif

