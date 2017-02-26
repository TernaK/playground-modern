//
//  playground-modern
//
//  Created by Terna Kpamber on 2/21/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Camera.hpp"
#include "Shader.hpp"
#include "GLTextureNode.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

GLTextureNode cube;
GLNode light;

Camera camera(glm::vec3(-0.1,0,5));
//  Camera camera(glm::vec3(-2,-2,5));

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  float d = 0.5;
  if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_UP) {
    camera.eye.z -= d;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_DOWN) {
    camera.eye.z += d;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_LEFT) {
    camera.eye.x -= d;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_RIGHT) {
    camera.eye.x += d;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_U) {
    camera.eye.y += d;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_D) {
    camera.eye.y -= d;
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
  
  
  vector<GLfloat> texCoords = {
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0, //front
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0, //back
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0, //left
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0, //rigt
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0, //top
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0 //bottom
  };
  
  glEnable(GL_DEPTH_TEST);
  
  cube = GLTextureNode("texture2.jpg", vertices, indices, normals, texCoords);
  cube.scale = glm::vec3(1.5,1.5,1.5);
  cube.init();
  
//  light = GLNode(vertices, indices, normals , texCoords);
//  light.init();
  
//  light.position = glm::vec3(-1, 0.9, 2);
  light.scale = glm::vec3(0.02,0.02,0.1);
  
  Light light0 = Light(glm::vec3(0.1), glm::vec3(1), glm::vec3(0.3), glm::vec3(1));
//  light0.position = glm::vec3(-0.5, 0.9, 3);
  cube.light = &light0;
  
  while(!glfwWindowShouldClose(window)){
    glfwPollEvents();
    
    glClearColor(0.15, 0.15, 0.15, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    camera.look();
    camera.perspective(glm::radians(45.0f), GLfloat(width)/GLfloat(height), 0.1f, 50.0f);
    
    //light
//    lightShader.use();
//    camera.setViewAndProjection(lightShader);
    
    glm::vec3 lightColor(1.0);
    //    lightColor.x = sin(glfwGetTime() * 2.0f);
    //    lightColor.y = sin(glfwGetTime() * 0.7f);
    //    lightColor.z = sin(glfwGetTime() * 1.3f);Image result for opengl cube
    //    light0.position = light.position;
    
    light0.diffuse = lightColor * glm::vec3(1); // Decrease the influence
    light0.ambient = lightColor * glm::vec3(1); // Low influence
    light0.specular = glm::vec3(0.3,0.5,0.3);
    
//    glUniform3fv(glGetUniformLocation(lightShader.program, "lightColor"), 1, glm::value_ptr(lightColor));
//    light.draw(lightShader);
    
    //cube
    shader.use();
    camera.setViewAndProjection(shader);
    
    glUniform3fv(glGetUniformLocation(shader.program, "eyePosition"), 1,  glm::value_ptr(camera.eye));
    
    cube.rotation += glm::vec3(0, 0.01, 0);
    cube.draw(shader);
    
    glfwSwapBuffers(window);
  }
  
  glfwTerminate();
  return 0;
}
