#include <graphics/Texture.h>

namespace engine {
    namespace graphics {
        
        Texture::Texture(const std::string& path) 
            : _path(path) 

        {
            if(not load()) 
                std::cerr << "Could not load image: " << path << std::endl;
        }

        Texture::~Texture() {
        
        }

        void Texture::bind() const {
            glBindTexture(GL_TEXTURE_2D, _textureID);
        }

        void Texture::unbind() const {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        bool Texture::load() {
            int num_comps;
            unsigned char* image_data = stbi_load(_path.c_str(), &_width, &_height, &num_comps, 4);
            
            if(image_data == NULL) 
                return false;
            
            glGenTextures(1, &_textureID);
            glBindTexture(GL_TEXTURE_2D, _textureID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

            glBindTexture(GL_TEXTURE_2D, 0);

            stbi_image_free(image_data);
            
            return true;
        }

    }
}
