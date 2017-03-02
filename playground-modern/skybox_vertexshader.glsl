#version 330 core

layout (location = 0) in vec3 skyboxCoord;

out vec3 SkyboxCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * vec4(skyboxCoord, 1.0);
  SkyboxCoord = skyboxCoord;
}
