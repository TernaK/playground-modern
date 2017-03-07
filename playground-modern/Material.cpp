//
//  Material.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/24/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include <glm/glm.hpp>
#include "Material.hpp"
using namespace std;

Material::Material(glm::vec3 ambient,
                   glm::vec3 diffuse,
                   glm::vec3 specular, GLfloat shininess)
{
  this->ambient = ambient;
  this->diffuse = diffuse;
  this->specular = specular;
  this->shininess = shininess;
};

void Material::setInShaderWithName(const Shader& shader, std::string uniformName,
                         bool useShader)
{
  if(useShader) shader.use();
  
  GLint loc = glGetUniformLocation(shader.program, uniformName.c_str());
  if(loc < 0)
    cerr << "ERROR::MATERIAL:: could not set material in shader: " << uniformName << endl;
  
  shader.setVector3f(uniformName+".ambient", this->ambient);
  shader.setVector3f(uniformName+".diffuse", this->diffuse);
  shader.setVector3f(uniformName+".specular", this->specular);
  shader.setFloat(uniformName+".shininess", this->shininess);
  
}
#include "Shader.hpp"
