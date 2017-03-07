#version 330 core

struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

in vec3 f_Normal;
in vec3 f_Position;

uniform vec3 lightColor;/* set by object or otherwise */
uniform vec3 lightPosition;/* set by object or otherwise */
uniform vec3 eyePosition;
uniform Material material;/* set by Material */

out vec4 color;

void main()
{
  /* ambient */
  vec3 ambient = lightColor * material.ambient;
  
  /* diffuse */
  vec3 normal = normalize(f_Normal);
  vec3 lightDirection = normalize(lightPosition - f_Position);
  float diffuseStrength = max(dot(lightDirection, normal), 0.0);
  vec3 diffuse = lightColor * (diffuseStrength * material.diffuse);
  
  /* specular */
  vec3 toEye = normalize(eyePosition - f_Position);
  vec3 reflection = reflect(-lightDirection, normal);
  float specularStrength = pow(max(dot(reflection, toEye), 0.0), material.shininess);
  vec3 specular = lightColor * (specularStrength * material.specular);

  color = vec4((ambient + diffuse + specular), 1.0f);
}
