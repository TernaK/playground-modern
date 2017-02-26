//
//  GLNode.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/22/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "GLNode.hpp"
using namespace std;

GLNode::GLNode() {
  
}

//GLNode::GLNode(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
//  assert(vertices.size() > 0 && indices.size() > 0);
//  this->vertices = vertices;
//  this->indices = indices;
//}

GLNode::GLNode(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals) {
  assert(vertices.size() > 0 && indices.size() > 0);
  this->vertices = vertices;
  this->indices = indices;
  this->normals = normals;
}


GLNode::~GLNode(){
  if(ready){
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
  }
}

void GLNode::init(){
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  
  //concatenate vertex color and normal data (vcn)
  vector<GLfloat> vertColNor;// = vertices;
  for(auto index: indices) {
    vertColNor.push_back(vertices[index * 3]);
    vertColNor.push_back(vertices[index * 3 + 1]);
    vertColNor.push_back(vertices[index * 3 +2]);
  }
  
  if(!normals.empty())
  	vertColNor.insert(vertColNor.end(), normals.begin(), normals.end());
  
  //convert vcn to c array
  GLfloat verticesNormalArray[vertColNor.size()];
  for(int i = 0 ; i < vertColNor.size(); i++)
    verticesNormalArray[i] = vertColNor[i];
  
  //offsets in the vcn array
  auto normalsOffset = 3 * sizeof(GLfloat) * indices.size();
  
  glBindVertexArray(VAO);
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesNormalArray), verticesNormalArray, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    if(!normals.empty()){
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)normalsOffset);
      glEnableVertexAttribArray(1);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  ready = true;
}


void GLNode::draw(const Shader& shader) {
  if(!ready) {
    puts("ERROR::GLNode::object not initialized");
  }
  
  //model
  model = glm::translate(glm::mat4(1.0f), position);
  model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, scale);
  
  glm::mat3 normalTransform = glm::mat3(inverse(transpose(model)));
  
  glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix3fv(glGetUniformLocation(shader.program, "normalTransform"), 1, GL_FALSE, glm::value_ptr(normalTransform));
  
  //material
  GLint matAmbientLoc  = glGetUniformLocation(shader.program, "material.ambient");
  GLint matDiffuseLoc  = glGetUniformLocation(shader.program, "material.diffuse");
  GLint matSpecularLoc = glGetUniformLocation(shader.program, "material.specular");
  GLint matShineLoc    = glGetUniformLocation(shader.program, "material.shininess");
  
  glUniform3fv(matAmbientLoc, 1, glm::value_ptr(material.ambient));
  glUniform3fv(matDiffuseLoc, 1, glm::value_ptr(material.diffuse));
  glUniform3fv(matSpecularLoc, 1, glm::value_ptr(material.specular));
  glUniform1f(matShineLoc, material.shininess);
  
  //light
  GLint lightAmbientLoc  = glGetUniformLocation(shader.program, "light.ambient");
  GLint lightDiffuseLoc  = glGetUniformLocation(shader.program, "light.diffuse");
  GLint lightSpecularLoc = glGetUniformLocation(shader.program, "light.specular");
  GLint lightPositionLoc    = glGetUniformLocation(shader.program, "light.position");
  
  glUniform3fv(lightAmbientLoc, 1, glm::value_ptr(light->ambient));
  glUniform3fv(lightDiffuseLoc, 1, glm::value_ptr(light->diffuse));
  glUniform3fv(lightSpecularLoc, 1, glm::value_ptr(light->specular));
  glUniform3fv(lightPositionLoc, 1, glm::value_ptr(light->position));
  
  glBindVertexArray(VAO);
  {
    glDrawArrays(GL_TRIANGLES, 0, GLint(indices.size()));
  }
  glBindVertexArray(0);
}

void GLNode::setNormals(const std::vector<GLfloat>& normals) {
  this->normals = normals;
}
