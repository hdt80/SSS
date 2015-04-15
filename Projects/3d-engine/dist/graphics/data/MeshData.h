#pragma once

#include <graphics/data/Mesh.h>

namespace engine {
    namespace graphics {
        
        class MeshData {
            private:
                unsigned short _references;
                const Mesh* _mesh;
            public:

                MeshData(Mesh* mesh);
                ~MeshData();

                inline const unsigned short getReferences() const { return _references; } 
                inline void addRefererence() { _references++; }
                inline void removeReference() { _references--; }
                
                const Mesh* getMesh() const;

            private:
            protected:

        };

    }
}
