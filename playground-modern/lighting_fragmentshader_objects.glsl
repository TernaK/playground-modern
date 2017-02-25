#version 330 core

in vec3 fColor;
in vec3 fNormal;
in vec3 fPosition;

out vec4 color;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 eyePosition;

//TODO: uniform float ambientStrength;
//TODO: uniform float specularStrength;

void main() {
  
  vec3 normalizedVertexToLight = normalize(lightPosition - fPosition);
  float normalComponent = max(dot(normalizedVertexToLight, fNormal), 0);
  
  //diffuse
  vec3 diffuse = normalComponent * lightColor;
  
  //ambient
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;
  
  //specular
  float specularStrength = 0.3;
  vec3 normalizedVertexToEye = normalize(eyePosition - fPosition);
  vec3 reflectDir = reflect(-normalizedVertexToEye, fNormal);
  float specularStrengthAtEye = pow(max(dot(normalizedVertexToEye, reflectDir), 0), 32);
  vec3 specular = specularStrength * specularStrengthAtEye * lightColor;
  
  vec3 result = (diffuse + ambient + specular) * fColor;
  
  color = vec4(result, 1.0f);
}
