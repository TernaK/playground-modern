//
//  TextureMaterial.hpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/25/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef TextureMaterial_hpp
#define TextureMaterial_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Texture.hpp"

class TextureMaterial {
public:
  Texture texture;
  glm::vec3 specular;
  GLfloat shininess;
  
  TextureMaterial();
  TextureMaterial(Texture texture, glm::vec3 specular, GLfloat shininess);
};

#endif /* TextureMaterial_hpp */
