#pragma once

#include <GL/glew.h>

namespace engine {
    namespace graphics {


        class IndexBuffer {
            private:
                /* location of this buffer on the GPU */
                GLuint _bufferID;
                /* the number of elements in this buffer */
                GLuint _count;

            public:
                /**
                 * Creates an index buffer out of the 
                 * given data
                 *
                 * @param data - array of all the indices
                 * @param count - the number of indices to be used
                 *
                 */
                IndexBuffer(const GLuint* data, GLsizei count);
                ~IndexBuffer();

                /* tells the GPU to use these indices */
                void bind() const;
                /* talls the GPU to stop using these indices */
                void unbind() const;

                inline GLuint getCount() const { return _count; }
            private:
            protected:
        };


    }
}
