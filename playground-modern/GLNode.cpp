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
  
  calculateNormals();
  
  //concatenate vertex color and normal data (vcn)
  vector<GLfloat> vertColNor = vertices;
  vertColNor.insert(vertColNor.end(), colors.begin(), colors.end());
  vertColNor.insert(vertColNor.end(), normals.begin(), normals.end());
  
  //convert vcn to c array
  GLfloat verticesColorArray[vertColNor.size()];
  for(int i = 0 ; i < vertColNor.size(); i++)
    verticesColorArray[i] = vertColNor[i];
  
  //convert to c array
  GLuint indicesArray[indices.size()];
  for(int i = 0 ; i < indices.size(); i++)
    indicesArray[i] = indices[i];
  
  //offsets in the vcn array
  auto colorOffset = sizeof(GLfloat) * vertices.size();
  auto normalsOffset = colorOffset + sizeof(GLfloat) * colors.size();
  
  glBindVertexArray(VAO);
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColorArray), verticesColorArray, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesArray), indicesArray, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)colorOffset);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)normalsOffset);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); DON'T!
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  ready = true;
}


void GLNode::draw(const Shader& shader) {
  if(!ready) {
    puts("ERROR::GLNode::object not initialized");
  }
  
  model = glm::translate(glm::mat4(1.0f), position);
  model = glm::scale(model, scale);
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

void GLNode::calculateNormals() {
  for(int i = 0; i < indices.size()/3; i++) {
    int index = indices[i*3] * 3; //index in the vertices array
    glm::vec3 p0(vertices[index], vertices[index+1], vertices[index+2]);
    index = indices[i*3+1] * 3;
    glm::vec3 p1(vertices[index], vertices[index+1], vertices[index+2]);
    index = indices[i*3+2] * 3;
    glm::vec3 p2(vertices[index], vertices[index+1], vertices[index+2]);
    glm::vec3 v1 = p1 - p0;
    glm::vec3 v2 = p2 - p0;
    glm::vec3 normal = glm::normalize(glm::cross(v2, v1));
    normals.push_back(normal.x);
    normals.push_back(normal.y);
    normals.push_back(normal.z);
  }
}
