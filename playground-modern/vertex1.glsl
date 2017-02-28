#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 Color;
out vec3 Position;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  Position = (model * vec4(position, 1.0)).xyz;
  gl_Position = projection * view * vec4(Position, 1.0);
  Color = color;
  TexCoord = texCoord;
}
