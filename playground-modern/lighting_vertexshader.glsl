#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
out vec3 fColor;
out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;

uniform vec3 objectColor;
uniform mat4 model;
uniform mat3 normalTransform;
uniform mat4 view;
uniform mat4 projection;

void main() {
  fPosition = (model * vec4(position, 1.0)).xyz;
  gl_Position = projection * view * vec4(fPosition, 1.0);
  fNormal = normalize(normalTransform * normal);
  fColor = objectColor;
  fTexCoord = texCoord;
}
