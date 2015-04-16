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
                Window(const std::string& title, int width, int height);
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
                
                bool init();

                friend void window_resize_callback(GLFWwindow* window, int width, int height);
                static void window_resize_callback(GLFWwindow* window, int width, int height);

            protected:
        };
    
    
    
    };
};
