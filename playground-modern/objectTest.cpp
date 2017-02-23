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

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GL_TRUE);
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
  
  GLFWwindow *window = glfwCreateWindow(640, 480, "hello modern opengl", nullptr, nullptr);
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
  
  //shader program
  Shader shader("vertex_shader.glsl","fragment_shader.glsl");
  
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
  vector<GLfloat> colors = {
    0.5f, 0.9f, 0.5f,
    0.8f, 0.1f, 0.5f,
    0.1f, 0.5, 1.0f,
    0.1f, 0.7f, 0.5f,
    
    0.8f, 0.1f, 0.5f,
    0.5f, 0.9f, 0.5f,
    0.1f, 0.5f, 1.0f,
    0.1f, 0.7f, 0.5f,
  };
  vector<GLuint> indices = {
    0,1,2, 1,2,3,
    1,5,3, 5,3,7,
    5,4,7, 4,7,6,
    4,0,6, 0,6,2,
    2,3,6, 3,6,7,
    4,5,0, 5,0,1
  };
  
  glEnable(GL_DEPTH_TEST);
  
  Camera camera;
  
  GLNode cube(vertices, colors, indices);
  cube.init();
  
  while(!glfwWindowShouldClose(window)){
    glfwPollEvents();
    
    
    glClearColor(0.2, 0.3, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shader.use();
    cube.draw();
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), GLfloat(glfwGetTime()*M_PI), glm::vec3(0.0f, -1.0f, 0.0f));
    glm::mat4 view = camera.lookAt(glm::vec3(0,1,5));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
    
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    
    glfwSwapBuffers(window);
  }
  
  glfwTerminate();
  return 0;
}
