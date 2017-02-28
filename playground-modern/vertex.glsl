#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 Color;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  Position = (model * vec4(position, 1.0)).xyz;
  gl_Position = projection * view * vec4(Position, 1.0);
  Color = color;
}
