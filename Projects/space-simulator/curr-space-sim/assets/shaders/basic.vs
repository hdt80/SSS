#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textCoord;
layout (location = 2) in vec3 normal;

out vec2 textCoord0;
out vec3 normal0;

uniform mat4 transform;
uniform mat4 perspective = mat4(1);

void main() {
    gl_Position = perspective * transform * vec4(position, 1.0);
    textCoord0 = textCoord;
    normal0 = normal;
}
