#version 330

layout (location = 0) out vec4 fragColor;

uniform vec4 light_color;
uniform vec2 light_pos;


in DATA {
    vec4 position;
    vec4 color;
    vec2 uv;
    float tid;
} fs_in;

uniform sampler2D textures[16];

void main() {
    float intensity = 1.0 / length(fs_in.position.xy - light_pos);
    if(fs_in.tid > 0.0) {
        int tid = int(fs_in.tid - 0.5);
        // fragColor = vec4(fs_in.tid / 10.0, 0, 0, 1);
        fragColor = texture(textures[tid], fs_in.uv);// * intensity;
    } else {
        fragColor = fs_in.color * intensity;
    }
}

