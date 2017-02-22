#version 330 core

out vec4 color;
in vec4 fColor;
in vec2 fTexCoord;
uniform sampler2D customTexture1;
uniform sampler2D customTexture2;
uniform float mixLevel;

void main() {
  color = mix(texture(customTexture1, fTexCoord), texture(customTexture2, fTexCoord), mixLevel);
}
