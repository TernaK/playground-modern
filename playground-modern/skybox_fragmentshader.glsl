#version 330 core

in vec3 SkyboxCoord;

out vec4 color;

uniform samplerCube skybox;

void main()
{
  color = texture(skybox, SkyboxCoord);
}
