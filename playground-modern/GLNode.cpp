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

GLNode::GLNode(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& colors, const std::vector<GLuint>& indices) {
  assert(vertices.size() == colors.size() && vertices.size() > 0);
  this->vertices = vertices;
  this->colors = colors;
  this->indices = indices;
}


GLNode::~GLNode(){
  if(ready){
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
  }
}

void GLNode::init(){
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  
  vector<GLfloat> vertCol = vertices;
  vertCol.insert(vertCol.end(), colors.begin(), colors.end());
//  GLfloat *verticesColorArray = &vertices[0];
//  GLuint *indicesArray = &indices[0];
  GLfloat verticesColorArray[vertCol.size()];
  for(int i = 0 ; i < vertCol.size(); i++)
    verticesColorArray[i] = vertCol[i];
  GLuint indicesArray[indices.size()];
  for(int i = 0 ; i < indices.size(); i++)
    indicesArray[i] = indices[i];
  auto colorOffset = sizeof(GLfloat) * vertices.size();
  
  glBindVertexArray(VAO);
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColorArray), verticesColorArray, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesArray), indicesArray, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)colorOffset);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  ready = true;
}


void GLNode::draw(const Shader& shader) {
  if(!ready) {
    puts("ERROR::GLNode::object not initialized");
  }
  
  model = glm::scale(glm::mat4(1.0f), scale);
  model = glm::translate(model, position);
  model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
  
  glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  glBindVertexArray(VAO);
  {
    glDrawElements(GL_TRIANGLES, GLuint(indices.size()), GL_UNSIGNED_INT, 0);
  }
  glBindVertexArray(0);
}
