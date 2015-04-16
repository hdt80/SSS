#include <components/RenderComponent.h>

namespace engine {
    namespace object {

        std::unordered_map<std::string, MeshData*> RenderComponent::loadedMeshes;
        std::unordered_map<std::string, TextureData*> RenderComponent::loadedTextures;

        RenderComponent::RenderComponent(const std::string& mesh_id, const std::string& texture_id, bool bin) 
            : _meshID(mesh_id), _textureID(texture_id)
        {
            if(not loadedMeshes.count(mesh_id)) {
                std::vector<Vertex> verts;
                std::vector<GLuint>    indices;
                if(bin)
                    MeshUtils::load_mesh_bin(mesh_id, verts, indices);
                else
                    MeshUtils::load_mesh_obj(mesh_id, verts, indices);
                loadedMeshes[mesh_id] = new MeshData(new Mesh(verts, indices));
            } else {
                loadedMeshes[mesh_id]->addReference();
            } 
            if (!texture_id.empty()) {
                if(!loadedTextures.count(texture_id)) {
                    loadedTextures[texture_id] = new TextureData(new Texture(texture_id));   
                } else {
                    loadedTextures[texture_id]->addReference();
                }
            }
        }


        RenderComponent::~RenderComponent() {
            loadedMeshes[_meshID]->removeReference();
            loadedTextures[_textureID]->removeReference();
            if(loadedMeshes[_meshID]->getReferences() == 0) {
                delete loadedMeshes[_meshID];
                loadedMeshes.erase(_meshID);
            }

            if(loadedTextures[_textureID]->getReferences() == 0) {
                delete loadedTextures[_textureID];
                loadedTextures.erase(_textureID);
            }
        }


        void RenderComponent::addMesh(const std::string& id, Mesh* mesh) {
            loadedMeshes[id] = new MeshData(mesh); 
        }

        void RenderComponent::addTexture(const std::string& id, Texture* texture) {
            loadedTextures[id] = new TextureData(texture);
        }
    }
}
