#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vColor;
out vec4 fColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model* vec4(position, 1.0);
  fColor = vec4(vColor, 1.0);
}
