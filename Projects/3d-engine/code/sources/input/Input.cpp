#include <input/Input.h>

namespace engine {

    bool Input::_keys[MAX_KEYS];
    bool Input::_mouseButtons[MAX_BUTTONS];
    double Input::_mouseX;
    double Input::_mouseY;


    void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        _keys[key] = action != GLFW_RELEASE; 
    }

    void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        _mouseButtons[button] = action != GLFW_RELEASE;
    }

    void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
        _mouseX = xpos;
        _mouseY = ypos;
    }

    void Input::init(GLFWwindow* window) {
        glfwSetKeyCallback(window, key_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);

        for(int i = 0; i < MAX_KEYS; i++) 
            _keys[i] = false;
        for(int i = 0; i < MAX_BUTTONS; i++)
            _mouseButtons[i] = false;

    }

    bool Input::isKeyPressed(unsigned int keyCode) {
        return _keys[keyCode];
    }

    bool Input::isMouseButtonPressed(unsigned int button) {
        return _mouseButtons[button];
    }

    void Input::getMousePosition(double& x, double& y) {
        x = _mouseX;
        y = _mouseY;
    }


}
