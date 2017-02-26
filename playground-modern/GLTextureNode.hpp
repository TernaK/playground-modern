//
//  GLTextureNode.hpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/25/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef GLTextureNode_hpp
#define GLTextureNode_hpp

#include "GLNode.hpp"
#include "Texture.hpp"
#include "TextureMaterial.hpp"
#include <SOIL/SOIL.h>
#include <vector>


class GLTextureNode : public GLNode  {
protected:
  std::vector<GLfloat> texCoords;
  TextureMaterial material;
  
public:
  
  GLTextureNode();
  
  GLTextureNode(TextureMaterial material, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals, const std::vector<GLfloat>& texCoords);
  
  GLTextureNode(std::string image, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals, const std::vector<GLfloat>& texCoords);
  
  void init();
  
  void draw(Shader shader);
  
  void setMaterial(TextureMaterial material) { this->material = material; };
};

#endif /* GLTextureNode_hpp */
