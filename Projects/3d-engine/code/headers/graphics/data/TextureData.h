#pragma once

#include <graphics/Texture.h>

namespace engine {
    namespace graphics {
    
        class TextureData {
            private:
                unsigned short _references;
                const Texture* _texture;
            public:
                TextureData(Texture* texture);
                ~TextureData();

                inline const unsigned short getReferences() const { return _references; }
                inline void addRefererence() { _references++; }
                inline void removeReference() { _references--; }

                const Texture* getTexture() const;
        };
            
    }
}
