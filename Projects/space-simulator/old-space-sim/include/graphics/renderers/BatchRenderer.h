#pragma once
#include <graphics/renderers/Renderer.h>
#include <graphics/data/Vertex.h>
#include <vector>
#include <cstddef>
#include <numeric>
#include <glm/gtc/matrix_access.hpp>
#include <components/RenderComponent.h>

namespace engine {
    namespace graphics {

        class BatchRenderer : public Renderer {
            private:
                
#define VERTEX_POINTER_SIZE sizeof(VertexPointer)
#define BUFFER_SIZE VERTEX_POINTER_SIZE * 100000
#define SHADER_VERTEX_INDEX 0

                GLuint _vao;
                std::vector<GLuint> _indices;
                VertexPointer* _buffer;
                GLuint _vbo;
                GLuint _vertexCount;

                std::vector<GLuint> _textureSlots;
                enum {
                    VERTEX_INDEX, COLOR_INDEX, UV_INDEX, NORMAL_INDEX, 
                    TEX_INDEX, TRANS_X, TRANS_Y, TRANS_Z, TRANS_W
                };

            public:
                BatchRenderer();
                ~BatchRenderer();

                void begin();
                void submit(const Actor* actor) override;
                void end();
                void flush() override;
            private:
                void init();
            protected:
        };

    }
}
