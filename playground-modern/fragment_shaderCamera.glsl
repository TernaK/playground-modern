#version 330 core

in vec4 fColor;
out vec4 color;
in vec2 fTexCoord;
uniform sampler2D customTexture1;
uniform sampler2D customTexture2;
uniform float mixLevel;

void main() {
  color = mix(texture(customTexture1, fTexCoord), texture(customTexture2, fTexCoord), mixLevel);
}
