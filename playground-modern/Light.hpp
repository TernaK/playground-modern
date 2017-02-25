//
//  Light.hpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/25/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <OpenGL/OpenGL.h>
#include <glm/glm.hpp>

class Light {
public:
  glm::vec3 position = glm::vec3(0,0,5);
  glm::vec3 ambient = glm::vec3(0.1);
  glm::vec3 diffuse = glm::vec3(1);
  glm::vec3 specular = glm::vec3(0.2);
  Light();
  Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position);
};

#endif /* Light_hpp */
