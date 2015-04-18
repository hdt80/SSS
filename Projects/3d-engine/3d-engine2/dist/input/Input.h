#pragma once

#include <GLFW/glfw3.h>

namespace engine {
#define MAX_KEYS 1024
#define MAX_BUTTONS 32
    /* this wil be a static class */
    class Input {
        private:
            static bool _keys[MAX_KEYS];
            static bool _mouseButtons[MAX_BUTTONS];

            static double _mouseX, _mouseY;

            static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
            static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

        public:
            static void init(GLFWwindow* window);

            static bool isKeyPressed(unsigned int keyCode);
            static bool isMouseButtonPressed(unsigned int button);
            static void getMousePosition(double& x, double& y);

    };

}
