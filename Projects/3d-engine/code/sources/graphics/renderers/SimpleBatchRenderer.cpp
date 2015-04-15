#include <graphics/renderers/SimpleBatchRenderer.h>
#include <iostream>

#define OFFSETOF(type, field) ((unsigned long) &(((type*)0)->field))

namespace engine {
    namespace graphics {

        SimpleBatchRenderer::SimpleBatchRenderer() {
            init();
        }

        SimpleBatchRenderer::~SimpleBatchRenderer() {
            glDeleteBuffers(1, &_vbo);
            glDeleteVertexArrays(1, &_vao);
        }

        void SimpleBatchRenderer::init() {
            _vertexCount = 0;
            glGenVertexArrays(1, &_vao);
            glBindVertexArray(_vao);

            glGenBuffers(1, &_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);

            glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

            glEnableVertexAttribArray(VERTEX_INDEX);
            glEnableVertexAttribArray(COLOR_INDEX);
            glEnableVertexAttribArray(TRANS_X);
            glEnableVertexAttribArray(TRANS_Y);
            glEnableVertexAttribArray(TRANS_Z);
            glEnableVertexAttribArray(TRANS_W);

            glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, 0);
            
            glVertexAttribPointer(COLOR_INDEX,  4, GL_UNSIGNED_BYTE, GL_TRUE, 
                                  VERTEX_POINTER_SIZE, (const GLvoid*)(OFFSETOF(VertexPointer, VertexPointer::color)));
           
            glVertexAttribPointer(TRANS_X, 4, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, (const GLvoid*)(OFFSETOF(VertexPointer, VertexPointer::transformX)));
            glVertexAttribPointer(TRANS_Y, 4, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, (const GLvoid*)(OFFSETOF(VertexPointer, VertexPointer::transformY)));
            glVertexAttribPointer(TRANS_Z, 4, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, (const GLvoid*)(OFFSETOF(VertexPointer, VertexPointer::transformZ)));
            glVertexAttribPointer(TRANS_W, 4, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, (const GLvoid*)(OFFSETOF(VertexPointer, VertexPointer::transformW)));

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

        }

        void SimpleBatchRenderer::begin() {
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            _buffer = (VertexPointer*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void SimpleBatchRenderer::submit(const Actor* actor) {
            if(not actor->isRenderable())
                return;
            
            const Mesh* mesh = actor->getRenderComponent()->getMesh();
            std::vector<GLuint> mapped = mesh->indices;
            std::transform(mapped.begin(), mapped.end(), mapped.begin(), std::bind1st(std::plus<GLuint>(), _vertexCount));
            _indices.insert(_indices.end(), mapped.begin(), mapped.end());

            glm::mat4 transform = actor->getTransformation();
           

            for(auto& v : mesh->vertices) {
                _buffer->position  = v.position;

                _buffer->color      = (int)(v.color.w * 225.0f) << 24 | (int)(v.color.z * 225.0f) << 16 
                                    | (int)(v.color.y * 225.0f) << 8  | (int)(v.color.x * 225.0f);
                _buffer->transformX = glm::column(transform, 0); 
                _buffer->transformY = glm::column(transform, 1); 
                _buffer->transformZ = glm::column(transform, 2); 
                _buffer->transformW = glm::column(transform, 3); 
                _buffer++;
                _vertexCount++;
            }

            if(_vertexCount > 20000) {
                end();
                flush();
                begin();
            }
        }

        void SimpleBatchRenderer::end() {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void SimpleBatchRenderer::flush() {
            _vertexCount = 0;
            glBindVertexArray(_vao);
            IndexBuffer ibo(&_indices[0], _indices.size());
            ibo.bind();

            glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, NULL);

            ibo.unbind();
            glBindVertexArray(0);
            _indices.clear();
        }

    }
}


