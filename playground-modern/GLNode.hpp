//
//  GLNode.hpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/22/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef GLNode_hpp
#define GLNode_hpp

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"

class GLNode {
private:
  GLuint VAO, VBO;
  std::vector<GLfloat> vertices;
  std::vector<GLuint> indices;
  std::vector<GLfloat> normals;
  bool ready = false;
  glm::mat4 model;

public:
  glm::vec3 color = glm::vec3(1,1,1);
  glm::vec3 rotation = glm::vec3(0,0,0);
  glm::vec3 position = glm::vec3(0,0,0);
  glm::vec3 scale = glm::vec3(1,1,1);
  
  GLNode();
//  GLNode(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
  GLNode(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals);
  ~GLNode();
  
  //bind buffers and arrays
  void init();
  
  //render using a shader
  void draw(const Shader& shader);
  
  void setNormals(const std::vector<GLfloat>& normals);
};

#endif /* GLNode_hpp */
