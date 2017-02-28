#version 330 core 

in vec3 Color;
in vec2 TexCoord;

uniform sampler2D textureMap;

out vec4 color;

void main() {
  color = texture(textureMap, TexCoord);
}
