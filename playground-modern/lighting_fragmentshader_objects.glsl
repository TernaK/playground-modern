#version 330 core

in vec3 fColor;
out vec4 color;

uniform vec3 lightColor;

void main() {
  float ambientStrength = 0.2f;
  vec3 ambient = ambientStrength * lightColor;
  vec3 result = ambient * fColor;
  
  color = vec4(result, 1.0f);
}
