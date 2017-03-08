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
#include "Shader.hpp"
#include "Material.hpp"

class GLNode
{
private:
  /* methods */
  void setMaterial(const Material& material) { this->material = material; };
  
  /* members */
  Material material;
  
protected:
  /* methods */
  void init(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& normals);
  void setUniformsInShader(const Shader& shader);
  
  /* members */
  GLsizei numPrimitives;
  GLuint VAO, VBO;

public:
  /* methods */
  GLNode();
  GLNode(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& normals);
  GLNode(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& normals, const std::vector<GLuint>& indices);
  ~GLNode();
  
  void draw(const Shader& shader);
  
  /* members */
  glm::vec3 rotation = glm::vec3(0,0,0);
  glm::vec3 position = glm::vec3(0,0,0);
  glm::vec3 scale = glm::vec3(1,1,1);
};

#endif /* GLNode_hpp */
