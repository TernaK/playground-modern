#version 330 core

in vec3 fColor;
out vec4 color;

uniform vec3 lightColor;

void main() {
  color = vec4(lightColor, 1.0);
}
