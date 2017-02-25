#version 330 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

in vec3 fColor;
in vec3 fNormal;
in vec3 fPosition;

out vec4 color;

uniform Material material;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 eyePosition;

void main() {
  
  //ambient
  vec3 ambient = lightColor * material.ambient;

  //diffuse
  vec3 normalizedVertexToLight = normalize(lightPosition - fPosition);
  float normalComponent = max(dot(normalizedVertexToLight, fNormal), 0);
  vec3 diffuse = lightColor * (normalComponent * material.diffuse);

  //specular
  vec3 normalizedVertexToEye = normalize(eyePosition - fPosition);
  vec3 reflectDir = reflect(-normalizedVertexToEye, fNormal);
  float specularStrengthAtEye = pow(max(dot(normalizedVertexToEye, reflectDir), 0), material.shininess);
  vec3 specular = lightColor * (specularStrengthAtEye * material.specular);
  
  vec3 result = (diffuse + ambient + specular);
  
  color = vec4(result, 1.0f);
}
