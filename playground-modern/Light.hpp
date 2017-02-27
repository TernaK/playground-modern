//
//  Light.hpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/25/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>

enum LightType {
  DIRECTIONAL=0,POINT=1,SPOTLIGHT=2
};

class Light {
public:
  glm::vec3 position = glm::vec3(0,0,5);
  glm::vec3 direction = glm::vec3(0,0,-1);
  
  glm::vec3 ambient = glm::vec3(0.1);
  glm::vec3 diffuse = glm::vec3(0.1);
  glm::vec3 specular = glm::vec3(0.05);
  
  GLfloat constant = 1;
  GLfloat linear = 0.09;
  GLfloat quadratic = 0.032;
  
  GLfloat cutoff = cos(glm::radians(20.0));
  
  LightType type = LightType::SPOTLIGHT;
  
  Light();
  
  Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position = glm::vec3(0,0,5), glm::vec3 direction = glm::vec3(0,0,-1));
};

#endif /* Light_hpp */
