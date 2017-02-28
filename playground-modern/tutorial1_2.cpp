//
//  tutorial1.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/27/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "Shader.hpp"
using namespace std;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
  string root = string(SRC) + "/";
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  GLFWwindow *window = glfwCreateWindow(600, 600, "tutorial 1", nullptr, nullptr);
  if(window == NULL)
  {
    puts("could not create window");
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);
  
  glewExperimental = true;
  if(glewInit() != GLEW_OK)
  {
    puts("glew init failed");
    glfwTerminate();
    exit(-1);
  }
  
  glfwSetKeyCallback(window, keyCallback);
  
  GLint width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, GLsizei(width), GLsizei(height));
  glEnable(GL_DEPTH_TEST);
  
  vector<GLfloat> data {
    -0.5, -0.5, 0,  1,0,0,
    0.5,  -0.5, 0,  0,1,0,
    0,    0.5,  0,  0,0,1,
  };
  
  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  
  glBindVertexArray(VAO);
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    {
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.size(), data.data(), GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  
  Shader shader(root+"playground-modern/vertex1.glsl", root+"playground-modern/fragment1.glsl");
  
  while(!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    
    glClearColor(0.1, 0.3, 0.4, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shader.use();
    glBindVertexArray(VAO);
    {
      glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
  }
  
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glfwTerminate();
  exit(0);
}
