#include <graphics/Window.h>
#include <graphics/Shader.h>
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <graphics/renderers/BatchRenderer.h>
#include <environment/Asteroid.h>
#include <actors/Prop.h>
#include <core/Game.h>
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <input/Input.h>

int main(int argc, char** agrv) {

    srand(time(NULL));

    using engine::graphics::Window;
    using engine::graphics::Shader;
    using engine::graphics::BatchRenderer;
    using engine::object::Prop;
    using engine::graphics::Camera;
    using engine::Input;
    using sss::Asteroid;

    Window window("sunset-space-simulator", 960, 540);
    glClearColor(0.3, 0.0, 0.3, 1.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
    glDepthMask(GL_TRUE);std::string file_path = "assets/shaders/textured";
    
    sss::Game game(Camera(glm::vec3(0, 0, 0), glm::quat(0, 0, 0, 1), glm::perspective(70.0f, 960.0f / 540.0f, 0.1f, 1000.0f)));
    while(not window.shouldClose()) {
        window.clear();

        game.update();
        game.render();

	if(Input::isKeyPressed(GLFW_KEY_ESCAPE))
	    break;
        window.update();
    }

    
    return 0;
}


