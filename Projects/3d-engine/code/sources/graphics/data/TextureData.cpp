#include <graphics/data/TextureData.h>

namespace engine {
    namespace graphics {
    
        TextureData::TextureData(Texture* texture) : _texture(texture) {
            addReference(); 
        }

        TextureData::~TextureData() {
            delete _texture;
        }

        const Texture* TextureData::getTexture() const {
            return _texture;
        }
    }
}


