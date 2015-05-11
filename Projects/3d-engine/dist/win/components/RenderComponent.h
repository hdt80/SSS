#pragma once

#include <components/Component.h>
#include <graphics/data/MeshData.h>
#include <graphics/data/TextureData.h>
#include <string>
#include <unordered_map>
#include <graphics/data/Vertex.h>
#include <utils/MeshUtils.h>

namespace engine {
    namespace object {
       
        using graphics::MeshData;
        using graphics::TextureData;
        using graphics::Mesh;
        using graphics::Texture;
        using graphics::Vertex;
        using utils::MeshUtils;

        class RenderComponent : public Component {
            private:
                static std::unordered_map<std::string, MeshData*> loadedMeshes;
                static std::unordered_map<std::string, TextureData*> loadedTextures;
                std::string _meshID;
                std::string _textureID;

            public:
                /**
                 * this constructor take in the path of a mesh to be created, and
                 * will not always add to the loadedMeshes map
                 * if the ID is already in the map,
                 * then it will use whatever mesh is stored there
                 * otherwise it will load a new mesh 
                 *
                 * @param mesh_id     - id of the mesh to be loaded
                 * @param texture_id  - id of the texture to be loaded
                 * @param bin         - if true load from binary, else parse
                 */
                RenderComponent(const std::string& mesh_id, const std::string& texture_id="", bool bin=false);

                /**
                 * The deconstuctor will play some part in garbage collection
                 */
                virtual ~RenderComponent();

                /* Not sure when one would use this function*/
                void update(Actor& actor, float delta=1.0f) {}

                inline const Mesh* getMesh() const { return loadedMeshes[_meshID]->getMesh(); }
                inline const Texture* getTexture() const { 
                    return (loadedTextures.count(_textureID) > 0) ? loadedTextures[_textureID]->getTexture() : nullptr;
                }

                static void addMesh(const std::string& id, Mesh* mesh);
                static void addTexture(const std::string& id, Texture* texture);
        };

    }
}
