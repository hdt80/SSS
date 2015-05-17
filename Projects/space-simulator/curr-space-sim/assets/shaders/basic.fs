#version 330

in vec2 textCoord0;
in vec3 normal0;
uniform sampler2D diffuse;
out vec4 fragColor;

void main() {
    // fragColor = vec4(0.0, 1.0, 0.0, 1.0);
    fragColor = texture(diffuse, textCoord0);// * (10.0 / length(textCoord0.x - normal0.xy));
    if(fragColor.a <= 0.1f)
        discard;
}

