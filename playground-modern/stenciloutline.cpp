//
//  playground-modern
//
//  Created by Terna Kpamber on 2/21/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Shader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

GLfloat mixLevel = 0.5;

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_UP) {
    mixLevel += 0.1;
  }
  if(action == GLFW_PRESS && key == GLFW_KEY_DOWN) {
    mixLevel -= 0.1;
  }
  mixLevel = mixLevel < 0 ? 0 : mixLevel;
  mixLevel = mixLevel > 1 ? 1 : mixLevel;
}

glm::vec3 getCameraUp(const glm::vec3& target, const glm::vec3& position) {
  glm::vec3 right = glm::normalize(glm::cross(-position, glm::vec3(0,1,0)));
  glm::vec3 up = glm::normalize(glm::cross(right, -position));
  return up;
};


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
  Shader shader("vertex_shaderCamera.glsl","fragment_shaderCamera.glsl");
  Shader outlineShader("vertex_shaderCamera.glsl","fragment_shaderStencil.glsl");
  
  GLfloat vertices[] = {
    -0.5f,-0.5f,0.5f,  0.0f, 0.0f,  0.5f, 0.9f, 0.5f,
    0.5f,-0.5,0.5f,    1.0f, 0.0f,  0.8f, 0.1f, 0.5f,
    -0.5f,0.5f,0.5f,   0.0f, 1.0f,  0.1f, 0.5, 1.0f,
    0.5f,0.5f,0.5f,    1.0f, 1.0f,  0.1f, 0.7f, 0.5f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.8f, 0.1f, 0.5f,
    0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.5f, 0.9f, 0.5f,
    -0.5f, 0.5f, -0.5f,   0.0f, 1.0f,  0.1f, 0.5f, 1.0f,
    0.5f, 0.5f, -0.5f,    1.0f, 1.0f,  0.1f,  0.7f, 0.5f,
    
  };
  GLuint indices[] = {
    0,1,2, 1,2,3,
    1,5,3, 5,3,7,
    5,4,7, 4,7,6,
    4,0,6, 0,6,2,
    2,3,6, 3,6,7,
    4,5,0, 5,0,1
  };
  
  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  
  glBindVertexArray(VAO);
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(5*sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  
  GLuint texture1, texture2;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int tw, th;
  unsigned char *image1 = SOIL_load_image("texture1.jpg", &tw, &th, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image1);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  unsigned char *image2 = SOIL_load_image("texture2.jpg", &tw, &th, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image2);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  while(!glfwWindowShouldClose(window)){
    glfwPollEvents();
    
    glClearColor(0.2, 0.3, 0.5, 1.0);
    
    /* object depth and stencil setup */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);//every fragment always pass the stencil test, set reference to 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);//if stencil test passes (which it is will), replace stencil value with ref(=1)
    glStencilMask(0xFF);//enable stencil buffer writing
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//clear after enabling (important!)
    
    glm::mat4 view, projection, model;
    glm::vec3 target(0,0,0);
    glm::vec3 position(0.0f,2.0f,4.0f);
    glm::vec3 scale(1.0,1.0,1.0);
    view = glm::lookAt(position, target, getCameraUp(target, position));
    projection = glm::perspective(glm::radians(45.0f), GLfloat(width)/height, 0.1f, 50.0f);
    
    /* draw object */
    shader.use();
    model = glm::rotate(model, GLfloat(glfwGetTime()*M_PI), glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, scale);
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(shader.program, "customTexture1"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(shader.program, "customTexture2"), 1);
    glUniform1f(glGetUniformLocation(shader.program, "mixLevel"), mixLevel);
    
    glBindVertexArray(VAO);
    {
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
    
    /* draw object outline: by drawing the same object scaled up */
    glDisable(GL_DEPTH_TEST); //we're not interested in depth testing
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);//fragment only pass stencil test if not equal to ref (=1)
    glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);//a fragment stencil value is set to 0 on passing test
    glStencilMask(0);//disable stencil buffer writing (because we don't want to do this)
    
    outlineShader.use();
    model = glm::rotate(glm::mat4(1.0), GLfloat(glfwGetTime()*M_PI), glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, scale * 1.05f);//scale image up
    glUniformMatrix4fv(glGetUniformLocation(outlineShader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(outlineShader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(outlineShader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    
    glBindVertexArray(VAO);
    {
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glfwTerminate();
  return 0;
}
