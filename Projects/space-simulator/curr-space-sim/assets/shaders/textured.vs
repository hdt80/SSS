#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;
layout (location = 4) in float textid;
layout (location = 5) in vec4 transformX;
layout (location = 6) in vec4 transformY;
layout (location = 7) in vec4 transformZ;
layout (location = 8) in vec4 transformW;


uniform mat4 perspective = mat4(1.0);

out DATA {
    vec4 position;
    vec4 color;
    vec2 uv;
    float tid;
} vs_out;

void main() {
    mat4 transform;
    transform[0] = transformX;
    transform[1] = transformY;
    transform[2] = transformZ;
    transform[3] = transformW;
    vec4 pos = transform * vec4(position, 1.0);
    gl_Position = perspective * pos;
    vs_out.position = pos;
    vs_out.color = color;
    vs_out.uv    = uv;
    vs_out.tid   = textid;
}
