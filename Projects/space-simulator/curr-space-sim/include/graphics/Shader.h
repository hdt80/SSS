#pragma once

#include <utils/FileUtils.h>
#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <unordered_map>

namespace engine {
    namespace graphics {
        class Shader {
            private:
                /* location of shader on the GPU */
                GLuint _shader;
                /* path of the vertex shader file */
                std::string _vertexShader;
                /* path of the fragment shader file */
                std::string _fragmentShader;
                mutable std::unordered_map<std::string, GLuint> _uniforms;

            public:
                /**
                 * constructs a shader from the given files
                 * 
                 * @param vertPath - path to the vertex shader
                 * @param fragPath - path to the fragment shader
                 *
                 */
                Shader(const std::string& vertPath, const std::string& fragPath);
                virtual ~Shader();


                /* the below functions sends data to the GPU to be used for all buffers */
                void setUniform1f(const std::string& name, float value) const;
                void setUniform1fv(const std::string& name, float* value, int count) const;
                void setUniform1i(const std::string& name, int value) const;
                void setUniform1iv(const std::string& name, int* value, int count) const;
                void setUniform2f(const std::string& name, const glm::vec2& vector) const;
                void setUniform3f(const std::string& name, const glm::vec3& vector) const;
                void setUniform4f(const std::string& name, const glm::vec4& vector) const;
                void setUniformMat4(const std::string& name, const glm::mat4& matrix) const;

                /* tells the GPU to use this shader */
                void bind() const;
                /* tells the GPU to stop using this shader */
                void unbind() const; 

            private:
                /**
                 * reads in the vertex and fragment shader,
                 * as well as compiles and linking them
                 *
                 * @return location of shader
                 */
                GLuint load();

                /**
                 * @param name - this is the name of the uniform in 
                 *               the shader
                 *
                 * @return the location of a uniform for the given name
                 */
                GLint getUniformLocation(const std::string& name) const;

                /* adds a uniform to the map */
                void addUniform(const std::string& name) const;

                static GLuint CURRENT_SHADER;
            protected:
        };
    }
}
