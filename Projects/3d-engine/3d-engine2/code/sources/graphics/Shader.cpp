#include <graphics/Shader.h>

namespace engine {

    namespace graphics {

        GLuint Shader::CURRENT_SHADER = 0;

        Shader::Shader(const std::string& vertPath, const std::string& fragPath) {
            _vertexShader = vertPath;
            _fragmentShader = fragPath;
            _shader = load();
        }

        Shader::~Shader() {
            glDeleteProgram(_shader);
        }

        GLuint Shader::load() {
            GLuint program  = glCreateProgram();
            GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

            std::string vertSourceString = utils::read_file(_vertexShader);
            std::string fragSourceString = utils::read_file(_fragmentShader);

            const char* vertSource = vertSourceString.c_str();
            const char* fragSource = fragSourceString.c_str();

            /* Vertex Shader */
            glShaderSource(vertex, 1, &vertSource, NULL);
            glCompileShader(vertex);

            GLint result;
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
            if(result == GL_FALSE) {
                GLint length;
                glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
                std::vector<char> error(length);
                glGetShaderInfoLog(vertex, length, &length, &error[0]);
                std::cout << "Vertex Shader Failed to Compile\n" << &error[0] << std::endl;
                glDeleteShader(vertex);
                return 0;
            }

            /* Fragment Shader */
            glShaderSource(fragment, 1, &fragSource, NULL);
            glCompileShader(fragment);

            glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
            if(result == GL_FALSE) {
                GLint length;
                glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
                std::vector<char> error(length);
                glGetShaderInfoLog(fragment, length, &length, &error[0]);
                std::cout << "Fragement Shader Failed to Compile\n" << &error[0] << std::endl;
                glDeleteShader(fragment);
                return 0;
            }

            glAttachShader(program, vertex);
            glAttachShader(program, fragment);

            glLinkProgram(program);
            glValidateProgram(program);

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            return program;
        }

        void Shader::bind() const {
            if(Shader::CURRENT_SHADER != _shader) {
                glUseProgram(_shader);
                Shader::CURRENT_SHADER = _shader;
            }
        }

        void Shader::unbind() const {
            glUseProgram(0);
            Shader::CURRENT_SHADER = 0;
        }

        GLint Shader::getUniformLocation(const std::string& name) const {
            return glGetUniformLocation(_shader, name.c_str()); 
        }

        void Shader::addUniform(const std::string& name) const {
            _uniforms[name] = getUniformLocation(name);
        }

        void Shader::setUniform1f(const std::string& name, float value) const {
            if(_uniforms.count(name) == 0)
                addUniform(name);
            glUniform1f(_uniforms[name], value);
        }
        
        void Shader::setUniform1fv(const std::string& name, float* value, int count) const {
            if(_uniforms.count(name) == 0)
                addUniform(name);
            glUniform1fv(_uniforms[name], count, value);
        }

        void Shader::setUniform1i(const std::string& name, int value) const {
            if(_uniforms.count(name) == 0)
                addUniform(name);
            glUniform1i(_uniforms[name], value); 
        }

        void Shader::setUniform1iv(const std::string& name, int* value, int count) const {
            if(_uniforms.count(name) == 0)
                addUniform(name);
            glUniform1iv(_uniforms[name], count, value); 
        }


        void Shader::setUniform2f(const std::string& name, const glm::vec2& vector) const {
            if(_uniforms.count(name) == 0)
                addUniform(name);    
            glUniform2f(_uniforms[name], vector.x, vector.y);
        }

        void Shader::setUniform3f(const std::string& name, const glm::vec3& vector) const {
            if(_uniforms.count(name) == 0)
                addUniform(name);
            glUniform3f(_uniforms[name], vector.x, vector.y, vector.z);
        } 

        void Shader::setUniform4f(const std::string& name, const glm::vec4& vector) const {
            if(_uniforms.count(name) == 0)
                addUniform(name);    
            glUniform4f(_uniforms[name], vector.x, vector.y, vector.z, vector.w);
        }

        void Shader::setUniformMat4(const std::string& name, const glm::mat4& matrix) const {
            if(_uniforms.count(name) == 0)
                addUniform(name);
            glUniformMatrix4fv(_uniforms[name], 1, GL_FALSE, &(matrix[0][0]));
        }
    }
}
