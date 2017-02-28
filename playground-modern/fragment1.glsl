#version 330 core 

in vec3 Color;
in vec2 TexCoord;
sampler2D textureMap;

out vec4 color;

void main() {
  color = vec4(texture(textureMap, TexCoord), 1.0);
}
