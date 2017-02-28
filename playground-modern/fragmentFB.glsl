#version 330 core 

layout (location = 0) out vec4 color;

in vec2 TexCoord;

uniform sampler2D renderedTexture;
uniform float time;

void main() {
  color = texture(renderedTexture, TexCoord + 0.005*vec2( sin(time+600.0*TexCoord.x),cos(time+600.0*TexCoord.y)) );
}
