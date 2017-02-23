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
  GLuint VAO, VBO, EBO;
  std::vector<GLfloat> vertices, colors;
  std::vector<GLuint> indices;
  bool ready = false;
  
public:
  glm::mat4 model;
  GLNode();
  GLNode(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& colors, const std::vector<GLuint>& indices);
  ~GLNode();
  void init();
  void draw();
};

#endif /* GLNode_hpp */
