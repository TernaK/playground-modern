//
//  playground-modern
//
//  Created by Terna Kpamber on 2/21/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Camera.hpp"
#include "Shader.hpp"
#include "GLNode.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

GLNode cube;
GLNode light;

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_UP) {
    light.position.z -= 0.05;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_DOWN) {
    light.position.z += 0.05;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_LEFT) {
    light.position.x -= 0.05;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_RIGHT) {
    light.position.x += 0.05;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_U) {
    light.position.y += 0.05;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_D) {
    light.position.y -= 0.05;
  }
}

int main(int argc, char * argv[]) {
  
  //glfw
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  GLFWwindow *window = glfwCreateWindow(600, 600, "hello modern opengl", nullptr, nullptr);
  if(window == nullptr){
    puts("failed to create glfw window");
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);
  
  //glew
  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK){
    puts("failed to create init glew");
    glfwTerminate();
    exit(-1);
  }
  
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  
  glfwSetKeyCallback(window, keyboardCallback);
  
  //shader programs
  Shader shader("lighting_vertexshader.glsl","lighting_fragmentshader_objects.glsl");
  Shader lightShader("lighting_vertexshader.glsl","lighting_fragmentshader.glsl");
  
  vector<GLfloat> vertices = {
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
  };
  
  vector<GLuint> indices = {
    0,1,2, 3,2,1,//front
    5,4,7, 6,7,4,//back
    4,0,6, 2,6,0,//left
    1,5,3, 7,3,5,//rigt
    2,3,6, 7,6,3,//top
    4,5,0, 1,0,5//bottom
  };
  
  vector<GLfloat> normals = {
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    
   	-1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f
  };
  
  glEnable(GL_DEPTH_TEST);
  
//  Camera camera(glm::vec3(1.6,2.5,5));
  Camera camera(glm::vec3(-2,-2,5));
  
  cube = GLNode(vertices, indices, normals);
  cube.scale = glm::vec3(1.5,1.5,1.5);
  cube.init();
  
  light = GLNode(vertices, indices, normals);
  light.init();
  
  light.position = glm::vec3(1, 0.9, 2);
  light.scale = glm::vec3(0.02,0.02,0.1);
  
  while(!glfwWindowShouldClose(window)){
    glfwPollEvents();
    
    glClearColor(0.15, 0.15, 0.15, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    camera.look();
    camera.perspective(glm::radians(45.0f), GLfloat(width)/GLfloat(height), 0.1f, 50.0f);
    
    //light
    lightShader.use();
    camera.setViewAndProjection(lightShader);
    
    glm::vec3 lightColor(0.8,0.8,0.8);
    glUniform3f(glGetUniformLocation(lightShader.program, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
    light.draw(lightShader);
    
    //cube
    shader.use();
    camera.setViewAndProjection(shader);
    
    glUniform3f(glGetUniformLocation(shader.program, "eyePosition"), camera.eye.x, camera.eye.y, camera.eye.z);
    glUniform3f(glGetUniformLocation(shader.program, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
    glUniform3f(glGetUniformLocation(shader.program, "lightPosition"), light.position.x, light.position.y, light.position.z);
    
//    cube.rotation += glm::vec3(0.01, 0,0);
    cube.draw(shader);
    
    glfwSwapBuffers(window);
  }
  
  glfwTerminate();
  return 0;
}
