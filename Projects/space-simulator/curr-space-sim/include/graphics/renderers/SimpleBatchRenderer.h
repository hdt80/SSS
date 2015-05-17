#pragma once
#include <graphics/renderers/Renderer.h>
#include <graphics/data/Vertex.h>
#include <vector>
#include <cstddef>
#include <numeric>
#include <glm/gtc/matrix_access.hpp>

namespace engine {
    namespace graphics {

        /* Simple in that it does not use textures */
        class SimpleBatchRenderer : public Renderer {
            private:
                
#define VERTEX_POINTER_SIZE sizeof(VertexPointer)
#define BUFFER_SIZE VERTEX_POINTER_SIZE * 100000
#define SHADER_VERTEX_INDEX 0

                GLuint _vao;
                std::vector<GLuint> _indices;
                VertexPointer* _buffer;
                GLuint _vbo;
                GLuint _vertexCount;

                enum {
                    VERTEX_INDEX, COLOR_INDEX, UV_INDEX,
                    NORMAL_INDEX, TRANS_X, TRANS_Y, TRANS_Z, TRANS_W
                };

            public:
                SimpleBatchRenderer();
                ~SimpleBatchRenderer();

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
