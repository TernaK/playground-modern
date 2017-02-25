#version 330 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
  vec3 position;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec3 fColor;
in vec3 fNormal;
in vec3 fPosition;

out vec4 color;

uniform Material material;
uniform Light light;
uniform vec3 eyePosition;

void main() {
  
  //ambient
  vec3 ambient = light.ambient * material.ambient;

  //diffuse
  vec3 normalizedVertexToLight = normalize(light.position - fPosition);
  float normalComponent = max(dot(normalizedVertexToLight, fNormal), 0);
  vec3 diffuse = light.diffuse * (normalComponent * material.diffuse);

  //specular
  vec3 normalizedVertexToEye = normalize(eyePosition - fPosition);
  vec3 reflectDir = reflect(-normalizedVertexToEye, fNormal);
  float specularStrengthAtEye = pow(max(dot(normalizedVertexToEye, reflectDir), 0), material.shininess);
  vec3 specular = light.specular * (specularStrengthAtEye * material.specular);
  
  vec3 result = (diffuse + ambient + specular);
  
  color = vec4(result, 1.0f);
}
