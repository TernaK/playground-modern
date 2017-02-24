//
//  Camera.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/22/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
: eye(eye),
	target(target),
	up(up) {
}

glm::mat4 Camera::look() {
  return lookTowards(eye, target);
}

glm::mat4 Camera::lookFrom(glm::vec3 eye){
  return lookTowards(eye, target);
}

glm::mat4 Camera::lookTowards(glm::vec3 eye, glm::vec3 target) {
  this->eye = eye;
  this->target = target;
  glm::vec3 right = glm::normalize(glm::cross(target-eye, glm::vec3(0,1,0)));
 	up = glm::normalize(glm::cross(right, target-eye));
  view = glm::lookAt(eye, target, up);
  return view;
}

glm::mat4 Camera::lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up) {
  this->eye = eye;
  this->target = target;
  this->up = up;
  view = glm::lookAt(eye, target, up);
  return view;
}


glm::mat4 Camera::perspective() {
  projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
  return projection;
}

glm::mat4 Camera::perspective(GLfloat fov_rad, GLfloat aspect, GLfloat zNear, GLfloat zFar) {
  this->fov = fov_rad;
  this->aspect = aspect;
  this->zNear = zNear;
  this->zFar = zFar;
  projection = glm::perspective(fov, aspect, zNear, zFar);
  return projection;
}
