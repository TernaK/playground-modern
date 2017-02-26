//
//  Texture.hpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/25/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>
#include <iostream>
#include <vector>
#include "Shader.hpp"

class Texture {
private:
  
public:
  bool ready = false;
  GLuint texture;
  GLubyte* data = nullptr;
  int width = 0, height = 0, channels = 0;
  
  Texture();
  
  Texture(GLubyte* data, int width, int height, int channels);
  
  Texture(std::string imageFile);
  
  Texture& operator = (Texture from);
  
  Texture(const Texture& from);
  
  void assign(GLubyte* data, int width, int height, int channels);
  
  ~Texture();
  
  void init();
  
  void activate(Shader shader);
  
};

#endif /* Texture_hpp */
