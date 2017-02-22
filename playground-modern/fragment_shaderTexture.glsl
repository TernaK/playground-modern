#version 330 core

out vec4 color;
in vec4 fColor;
in vec2 fTexCoord;
uniform sampler2D fTexture;

void main() {
  color = texture(fTexture, fTexCoord);
}
