#include <graphics/data/MeshData.h>

namespace engine {
    namespace graphics {

        MeshData::MeshData(Mesh* mesh) : _mesh(mesh) {
            addReference();
        }

        MeshData::~MeshData() {
            delete _mesh;
        }

        const Mesh* MeshData::getMesh() const {
            return _mesh;
        }

    }
}
