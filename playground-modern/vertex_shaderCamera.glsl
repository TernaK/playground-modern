#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 texCoord;
out vec4 fColor;
out vec2 fTexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model* vec4(position, 1.0);
  fColor = vec4(vColor, 1.0);
  fTexCoord = vec2(texCoord.s, 1.0 - texCoord.t);
}
