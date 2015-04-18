#version 330

uniform vec4 light_color;
uniform vec2 light_pos;

in vec4 color0;
in vec4 position0;

out vec4 fragColor;

void main() {
    float intensity = 1.0 / length(position0.xy - light_pos);
    fragColor = color0 * intensity;
}

