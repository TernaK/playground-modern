#version 330 core

in vec3 fColor;
in vec3 fNormal;
in vec3 fPosition;

out vec4 color;

uniform vec3 lightColor;
uniform vec3 lightPosition;

void main() {
  
  vec3 normalToLight = normalize(lightPosition - fPosition);
  float diffuseStrength = max(dot(normalToLight, fNormal), 0.0);
  vec3 diffuse = diffuseStrength * lightColor;
  
  float ambientStrength = 0.5f;
  vec3 ambient = ambientStrength * lightColor;
  vec3 result = (ambient + diffuse) * fColor;
  
  color = vec4(result, 1.0f);
}
