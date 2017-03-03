#version 330 core

layout (location = 0) in vec3 skyboxCoord;

out vec3 SkyboxCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
  vec4 position = projection * view * vec4(skyboxCoord, 1.0);
  gl_Position = position.xyww;
  SkyboxCoord = skyboxCoord;
}
