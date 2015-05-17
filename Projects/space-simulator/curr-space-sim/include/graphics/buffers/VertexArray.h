#pragma once

#include <GL/glew.h>
#include <vector>
#include <graphics/buffers/Buffer.h>

namespace engine {
    namespace graphics {
        
        class VertexArray {
            private:
                /* location of this vertex array on GPU*/
                GLuint _arrayID;
                /* List of the buffers to be added to this VAO, allowing memory management */
                std::vector<Buffer*> _buffers;

            public:
                VertexArray();
                ~VertexArray();

                /**
                 * adds a buffer to this VAO
                 *
                 * @param buffer - the buffer to be added
                 * @param index  - this value corresponds to the 
                 *                 location of the buffer element
                 *                 within the shader i.e. 
                 *                 layout (location = index) data
                 */
                void addBuffer(Buffer* buffer, GLuint index);
               
                /* tells the GPU to use this VAO */
                void bind() const;
                /* tells the GPU to stop using this VAO */
                void unbind() const;
                
            private:
            protected:
        };
        
    }
}
