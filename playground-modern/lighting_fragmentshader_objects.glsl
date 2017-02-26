#version 330 core

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct Light {
  vec3 position;
  vec3 direction;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  
  float constant;
  float linear;
  float quadratic;
  
  int type;
};

in vec3 fColor;
in vec3 fNormal;
in vec3 fPosition;
in vec2 fTexCoord;

out vec4 color;

uniform Material material;
uniform Light light;//TODO: implement multiple lights
uniform vec3 eyePosition;

void main() {
  
  float distance = length(light.position - fPosition);
  float attenuation = 1.0f/(light.constant + light.linear * distance + light.quadratic * distance * distance);
  
  vec3 texColor = vec3(texture(material.diffuse, fTexCoord));
  
  //ambient
  vec3 ambient = light.ambient * texColor;

  //diffuse
  vec3 normalizedVertexToLight;
  switch (light.type) {
  case 0:
    normalizedVertexToLight = normalize(-light.direction);
    break;
    
  default:
    normalizedVertexToLight = normalize(light.position - fPosition);
    break;
  }
  float normalComponent = max(dot(normalizedVertexToLight, fNormal), 0);
  vec3 diffuse = light.diffuse * (normalComponent * texColor);

  //specular
  vec3 normalizedVertexToEye = normalize(eyePosition - fPosition);
  vec3 reflectDir = reflect(-normalizedVertexToEye, fNormal);
  float specularStrengthAtEye = pow(max(dot(normalizedVertexToEye, reflectDir), 0), material.shininess);
  vec3 specular = light.specular * (specularStrengthAtEye * vec3(texture(material.specular, fTexCoord)));
  
  vec3 result = attenuation * (diffuse + ambient + specular);
  
  color = vec4(result, 1.0f);
}
