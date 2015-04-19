#include <iostream>
#include <graphics/Window.h>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <graphics/data/Vertex.h>
#include <graphics/data/Mesh.h>
#include <graphics/buffers/Buffers.h>
#include <graphics/Shader.h>
#include <graphics/renderers/BatchRenderer.h>
#include <actors/Prop.h>
#include <utils/MeshUtils.h>
#include <time.h>
#include <input/Input.h>
#include "testing/Player.h"
#include <cstdio>

#define LOTS_OF_SPRITES 0

using namespace engine;
using namespace graphics;
using namespace object;
using namespace utils;

Mesh* createRectangle(float x, float y, float width, float height);

int main(int argc, char** argv) {
    srand(time(NULL));
    Window window("engine", 960, 540);
    std::cout << glGetString(GL_VERSION) << std::endl;
    glClearColor(0, 0.3, 0.3, 1.0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
    glDepthMask(GL_TRUE);

    Shader shader("assets/shaders/textured.vs", "assets/shaders/textured.fs");
    shader.bind();
    shader.setUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
    
    int texts[16] = {0};
    shader.setUniform1iv("textures", texts, 16);

#if LOTS_OF_SPRITES
    shader.setUniformMat4("perspective", glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
#else
    shader.setUniformMat4("perspective", glm::perspective(70.0f, 960.0f / 540.0f, 0.1f, 1000.0f));
#endif
    shader.setUniform4f("light_color", glm::vec4(0.2, 0.4, 0.8, 1.0f));

#if LOTS_OF_SPRITES
    RenderComponent::addMesh("RECT", createRectangle(0, 0, 0.45, 0.45));
    std::vector<Prop*> props;
    for(float x = 0; x < 16; x += 0.5) {
        for(float y = 0; y < 9; y += 0.5) {
            Prop* p = new Prop(new RenderComponent("RECT"));
            p->setPosition(glm::vec3(x + 0.5, y + 0.5, 0));
            props.push_back(p);
        }
    }
    std::cout << "Rendering " << props.size()*4 << " vertices" << std::endl;
#else 
    Player* player = new Player(glm::vec3(0,  0, -10), 1);
#endif


    BatchRenderer renderer;

    while(not window.shouldClose()) {
        window.clear();

        double x, y;
        Input::getMousePosition(x, y);
        shader.setUniform2f("light_pos", glm::vec2((float)(-8.0f + x * 16.0f / 960.0f), 
                    (float)(4.5f - y * 9.0f / 540.0f)));
        renderer.begin();
        glm::vec3 AXIS(0, 1, 0);
#if LOTS_OF_SPRITES
        for(auto& m : props) {
            // m->rotate(AXIS, 1);
            renderer.submit(m);
        }
#else
        player->tick(1.0f);

        renderer.submit(player);
#endif
        renderer.end();
        renderer.flush();


        window.update();
    }
    return 0;
}

Mesh* createRectangle(float x, float y, float width, float height) {

    std::vector<Vertex> verts = {
        Vertex(glm::vec3(x, y, 0),                  glm::vec4(rand() % 1000 / 1000.0f, 0, 0, 1)),
        Vertex(glm::vec3(x, y + height, 0),         glm::vec4(0, rand() % 1000 / 1000.0f, 0, 1)),
        Vertex(glm::vec3(x + width, y + height, 0), glm::vec4(0, 0, rand() % 1000 / 1000.0f, 1)),
        Vertex(glm::vec3(x + width, y, 0),          glm::vec4(0, 0, 0, 1))
    };

    std::vector<GLuint> indices = {0, 3, 2, 2, 1, 0};

    return new Mesh(verts, indices);
}
