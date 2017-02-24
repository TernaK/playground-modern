#version 330 core

in vec3 fColor;
in vec3 fNormal;
in vec3 fPosition;

out vec4 color;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 eyePosition;

void main() {
  float ambientStrength = 1.0f;
  vec3 vecToLight = lightPosition - fPosition;
  float magLightOnNormal = ambientStrength * dot(vecToLight, fNormal) / length(vecToLight);
  vec3 vecToEye = eyePosition - fPosition;
  float distanceToEye = length(vecToEye);
  float cosTheta = dot(fNormal, vecToEye) / distanceToEye;
  ambientStrength = cosTheta * magLightOnNormal;
  
  vec3 ambient = ambientStrength * lightColor;
  vec3 result = ambient * vec3(1.0, 1.0, 1.0);/*fColor*/;
  
  color = vec4(result, 1.0f);
}
