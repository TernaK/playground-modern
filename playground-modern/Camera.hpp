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
public:
  glm::vec3 eye;
  glm::vec3 target;
  glm::vec3 up;
  glm::mat4 view;
  glm::mat4 projection;
  GLfloat fov = glm::radians(45.0f);
  GLfloat aspect = 1.0f;
  GLfloat zNear = 0.1;
  GLfloat zFar = 50;
  
  Camera(
         glm::vec3 eye = glm::vec3(0,0,1),
         glm::vec3 target = glm::vec3(0,0,0),
         glm::vec3 up = glm::vec3(0,1,0));
  glm::mat4 look();
  glm::mat4 lookFrom(glm::vec3 eye);
  glm::mat4 lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
  glm::mat4 lookTowards(glm::vec3 eye, glm::vec3 target);
  glm::mat4 perspective();
  glm::mat4 perspective(GLfloat fov, GLfloat aspect, GLfloat zNear, GLfloat zFar);
  glm::mat4 getView() { return view; };
  glm::vec3 getEye() { return eye; }
  glm::vec3 getTarget() { return target; };
  glm::vec3 getUp() { return up; };
};

#endif /* Camera_hpp */
