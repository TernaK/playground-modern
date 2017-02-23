//
//  Camera.hpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/22/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
  glm::mat4 view;
  glm::vec3 eye;
  glm::vec3 target;
  glm::vec3 up;
  
public:
  Camera(
         glm::vec3 eye = glm::vec3(0,0,1),
         glm::vec3 target = glm::vec3(0,0,0),
         glm::vec3 up = glm::vec3(0,1,0));
  glm::mat4 lookAt(glm::vec3 eye);
  glm::mat4 lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
  glm::mat4 lookAt(glm::vec3 eye, glm::vec3 target);
  glm::mat4 getView() { return view; };
  glm::vec3 getEye() { return eye; }
  glm::vec3 getTarget() { return target; };
  glm::vec3 getUp() { return up; };
};

#endif /* Camera_hpp */
