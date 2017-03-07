#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 f_Position;
out vec3 f_Normal;

uniform mat4 model;
uniform mat3 normalTransform;
uniform mat4 view;
uniform mat4 projection;

void main() {
  f_Position = (model * vec4(position, 1.0)).xyz;
  gl_Position = projection * view * vec4(f_Position, 1.0);
  f_Normal = normalize(normalTransform * normal);
}
