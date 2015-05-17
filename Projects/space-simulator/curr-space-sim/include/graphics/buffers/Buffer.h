#pragma once

#include <GL/glew.h>

namespace engine {
    namespace graphics {

        class Buffer {
            private:
                /* location of this buffer on the GPU */
                GLuint _bufferID;
                /* count of floats per datum in this buffer, i.e. 3 for vec3, 4 for vec4*/
                GLuint _componentCount;

            public:
                /**
                 * Creates a float buffer with the given data
                 *
                 * @param data - array of all the floats to be sent to the
                 *               GPU
                 *
                 * @param count - the number of elements in this array
                 * 
                 * @param componentCount - number of floats per datum
                 *
                 */
                Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
                ~Buffer();
                
                /* tells the GPU to use this buffer */
                void bind() const;
                /* tells the GPU to stop using this buffer */
                void unbind() const;

                /* returns the number of floats per datum */
                inline GLuint getComponentCount() const { return _componentCount; }
            private:
            protected:
        };

    }
}
