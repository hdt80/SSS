#include <graphics/Window.h>


namespace engine {
    namespace graphics {

        Window::Window(const std::string& title, int width, int height, bool fullscreen) {
            _title = title;
            _width = width;
            _height = height;
            if(init(fullscreen) == false) 
                glfwTerminate();
        }

        Window::~Window() {
            glfwTerminate(); 
        }

        bool Window::init(bool fullscreen) {

            if(not glfwInit()) {
                std::cout << "Failed to initialize GLFW" << std::endl;
                return false;
            }
#if defined __APPLE__ 
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif 
            
            if(fullscreen) {
                GLFWmonitor* primary = glfwGetPrimaryMonitor();
                const GLFWvidmode* vidMode = glfwGetVideoMode(primary);
                _width = vidMode->width;
                _height = vidMode->height;
                _window = glfwCreateWindow(_width, _height, _title.c_str(), primary, NULL);
            } else {
                _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL); 
            }

            if(not _window) {
                glfwTerminate();
                std::cout << "Failed to create GLFW Window!" << std::endl;
                return false;
            }

            glfwMakeContextCurrent(_window);
            glfwSetWindowUserPointer(_window, this);
            glfwSetWindowSizeCallback(_window, window_resize_callback);
            Input::init(_window);           

            glewExperimental = GL_TRUE;
            if(glewInit() != GLEW_OK) {
                std::cout << "Could not initialize GLEW!" << std::endl;
                return false;    
            }


            return true;
        }

        bool Window::shouldClose() const {
            return glfwWindowShouldClose(_window);
        }

        void Window::clear() const {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void Window::update() const {
            glfwPollEvents();
            glfwSwapBuffers(_window);
        }

        
        /*************************************************
         * glfw callbacks
         *************************************************/
        void Window::window_resize_callback(GLFWwindow* window, int width, int height) {
            Window* w = (Window*)glfwGetWindowUserPointer(window);
            w->_width = width;
            w->_height = height;
            glViewport(0, 0, width, height);
        }
    };
};
