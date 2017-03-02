//
//  tutorial4_6.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/27/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>
#include "Shader.hpp"
using namespace std;

//typedef struct Camera {
//  GLfloat horizontal = 0;
//  GLfloat vertical = 0;
//  GLfloat speed = 3;
//  glm::vec3 position = glm::vec3(0,0,5);
//  glm::vec3 direction = glm::vec3(0,0,-1);
//} Camera;
//
//GLfloat mouseSpeed = 0.003;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(window, GL_TRUE);
  
  switch (key) {
    case GLFW_KEY_UP:
      break;
      
    default:
      break;
  }
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
    -0.5, -0.5, 0,  1,0,0, 	0,1,
    0.5, -0.5, 0,  	0,1,0, 	1,1,
    0, 0.5,  0,  		0,0,1, 	0.5,0
  };
  
  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  
  glBindVertexArray(VAO);
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    {
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.size(), data.data(), GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  
  Shader shader(root+"playground-modern/vertex1.glsl", root+"playground-modern/fragment1.glsl");
  GLfloat rotation = 0;
  
  //texture
  int tw, th;
  GLubyte *image = SOIL_load_image("texture1.jpg", &tw, &th, 0, SOIL_LOAD_RGB);
  assert(image);
  
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  SOIL_free_image_data(image);
  
  double lastTime = glfwGetTime();
  int nbFrames = 0;
  
  while(!glfwWindowShouldClose(window))
  {
    // Measure speed
    double currentTime = glfwGetTime();
    nbFrames++;
    if ( currentTime - lastTime >= 2.0 ){ // If last prinf() was more than 1 sec ago
      // printf and reset timer
      printf("%.1f ms/frame\n", 2000.0/double(nbFrames));
      nbFrames = 0;
      lastTime += 2.0;
    }

    glfwPollEvents();
    
    glClearColor(0.1, 0.3, 0.4, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shader.use();
    
    rotation += 1;
    
    //transformation
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0,0,1));
    glm::mat4 view = glm::lookAt(glm::vec3(0,0,5), glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), GLfloat(width)/GLfloat(height), 0.1f, 100.0f);
    
    GLint modelLoc = glGetUniformLocation(shader.program, "model");
    GLint viewLoc = glGetUniformLocation(shader.program, "view");
    GLint projectionLoc = glGetUniformLocation(shader.program, "projection");
    
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    //texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    GLint textureLoc = glGetUniformLocation(shader.program, "textureMap");
    glUniform1i(textureLoc, 0);
    
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
