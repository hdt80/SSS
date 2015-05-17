#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <utils/stb_image.h>

namespace engine {
    namespace graphics {
        
        class Texture {
            private:
                const std::string _path;
                GLuint _textureID;
                int _width, _height;

            public:
                Texture(const std::string& path);
                ~Texture();

                void bind() const;
                void unbind() const;

                inline const int getWidth() const { return _width; }
                inline const int getHeight() const { return _height; }
                inline const GLuint getTextureID() const { return _textureID; }

            private:
                bool load();

        };

    }
}
