#include <graphics/renderers/BatchRenderer.h>
#include <iostream>

#define OFFSETOF(type, field) ((unsigned long) &(((type*)0)->field))

namespace engine {
    namespace graphics {

        BatchRenderer::BatchRenderer() {
            init();
        }

        BatchRenderer::~BatchRenderer() {
            glDeleteBuffers(1, &_vbo);
            glDeleteVertexArrays(1, &_vao);
        }

        void BatchRenderer::init() {
            _vertexCount = 0;
            glGenVertexArrays(1, &_vao);
            glBindVertexArray(_vao);

            glGenBuffers(1, &_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);

            glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

            glEnableVertexAttribArray(VERTEX_INDEX);
            glEnableVertexAttribArray(COLOR_INDEX);
            glEnableVertexAttribArray(UV_INDEX);
            glEnableVertexAttribArray(TEX_INDEX);
            glEnableVertexAttribArray(TRANS_X);
            glEnableVertexAttribArray(TRANS_Y);
            glEnableVertexAttribArray(TRANS_Z);
            glEnableVertexAttribArray(TRANS_W);

            glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, 0);
            glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_POINTER_SIZE, (const GLvoid*)OFFSETOF(VertexPointer, VertexPointer::color));
            glVertexAttribPointer(UV_INDEX, 2, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, (const GLvoid*)OFFSETOF(VertexPointer, VertexPointer::uv));
            glVertexAttribPointer(TEX_INDEX, 1, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, (const GLvoid*)OFFSETOF(VertexPointer, VertexPointer::texture_id));
            glVertexAttribPointer(TRANS_X, 4, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, (const GLvoid*)(OFFSETOF(VertexPointer, VertexPointer::transformX)));
            glVertexAttribPointer(TRANS_Y, 4, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, (const GLvoid*)(OFFSETOF(VertexPointer, VertexPointer::transformY)));
            glVertexAttribPointer(TRANS_Z, 4, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, (const GLvoid*)(OFFSETOF(VertexPointer, VertexPointer::transformZ)));
            glVertexAttribPointer(TRANS_W, 4, GL_FLOAT, GL_FALSE, VERTEX_POINTER_SIZE, (const GLvoid*)(OFFSETOF(VertexPointer, VertexPointer::transformW)));

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

        }

        void BatchRenderer::begin() {
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            _buffer = (VertexPointer*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void BatchRenderer::submit(const Actor* actor) {

            if(not actor->isRenderable())
                return;
            
            const object::RenderComponent* render = actor->getRenderComponent();
            std::vector<GLuint> mapped = render->getMesh()->indices;
            std::transform(mapped.begin(), mapped.end(), mapped.begin(), std::bind1st(std::plus<GLuint>(), _vertexCount));
            _indices.insert(_indices.end(), mapped.begin(), mapped.end());

            glm::mat4 transform = actor->getTransformation();
            float ts = 0.0f;
            if(render->getTexture() != nullptr) {
                GLuint tid = render->getTexture()->getTextureID();
                bool found = false;
                for(int i = 0; i < _textureSlots.size(); i++) {
                    if(_textureSlots[i] == tid) {
                        ts = (float)(i + 1);
                        found = true;
                        break;
                    }
                }

                if(not found) {
                    if(_textureSlots.size() >= 16) {
                        end();
                        flush();
                        begin();
                    } 
                    _textureSlots.push_back(tid);
                    ts = (float)_textureSlots.size();
                }
            }

            for(auto& v : render->getMesh()->vertices) {
                _buffer->position  = v.position;

                _buffer->color      = (int)(v.color.w * 225.0f) << 24 | (int)(v.color.z * 225.0f) << 16 
                                    | (int)(v.color.y * 225.0f) << 8  | (int)(v.color.x * 225.0f);
                _buffer->uv         = v.uv;
                _buffer->texture_id = ts;
                _buffer->transformX = glm::column(transform, 0); 
                _buffer->transformY = glm::column(transform, 1); 
                _buffer->transformZ = glm::column(transform, 2); 
                _buffer->transformW = glm::column(transform, 3); 
                _buffer++;
                _vertexCount++;
            }

            // if(_vertexCount > 20000) {
            //     end();
            //     flush();
            //     begin();
            // }
        }

        void BatchRenderer::end() {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void BatchRenderer::flush() {
            for(int i = 0; i < _textureSlots.size(); i++) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, _textureSlots[i]);
            }
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


