#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <input/Input.h>

namespace engine {
    namespace graphics {

        class Window {
            friend class Input;
            public:
                /**
                 * 
                 * @param title      - this will become the title of the window
                 * @param width      - this will be the width of the window, unless fullscreen is true
                 * @param height     - this will be the height of the window, unless fullscreen is true
                 * @param fullscreen - flag, if true then the window will be fullscreen,
                 *                           if false then the size will be the specified size
                 *
                 */
                Window(const std::string& title, int width, int height, bool fullscreen=false);
                ~Window();

                void update() const;
                bool shouldClose() const;
                void clear() const;

                inline int getWidth() const { return _width; }
                inline int getHeight() const { return _height; }

                
            private:
                int _width;
                int _height;
                std::string _title;
                GLFWwindow* _window;
                
                bool init(bool fullscreen);

                friend void window_resize_callback(GLFWwindow* window, int width, int height);
                static void window_resize_callback(GLFWwindow* window, int width, int height);

            protected:
        };
    
    
    
    }
}
