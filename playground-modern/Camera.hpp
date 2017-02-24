//
//  Camera.hpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/22/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Shader.hpp"
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
  GLfloat fov = glm::radians(45.0f); //fov must be in radians
  GLfloat aspect = 1.0f;             //aspect ratio
  GLfloat zNear = 0.1;               //near clipping plane z
  GLfloat zFar = 50.0f;                 //far clipping plane z
  
  Camera(glm::vec3 eye = glm::vec3(0,0,1),
         glm::vec3 target = glm::vec3(0,0,0),
         glm::vec3 up = glm::vec3(0,1,0));
  
  //use the internal eye point, target and up vectors
  glm::mat4 look();
  
  //set a new eye point and look from there
  glm::mat4 lookFrom(glm::vec3 eye);
  
  //set a new eye point, target and up vector
  glm::mat4 lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
  
  //set a new eye & target, then calculate the up vector and look
  glm::mat4 lookTowards(glm::vec3 eye, glm::vec3 target);
  
  //perspective projection using internal state
  glm::mat4 perspective();
  
  //set the state for the projection
  glm::mat4 perspective(GLfloat fov_radians, GLfloat aspect, GLfloat zNear, GLfloat zFar);
  
  //pass the view and projection matrices to a shader
  void setViewAndProjection(Shader shader);
  
//  glm::mat4 getView() { return view; };
//  glm::vec3 getEye() { return eye; }
//  glm::vec3 getTarget() { return target; };
//  glm::vec3 getUp() { return up; };
};

#endif /* Camera_hpp */
