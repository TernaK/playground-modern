//
//  main.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/21/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

GLuint getShaderProgram(string vertexShaderPath, string fragmentShaderPath) {
  
  //vertex shader
  ifstream ifs(vertexShaderPath);
  stringstream ss;
  ss << ifs.rdbuf();
  ifs.close();
  string vertexShaderSourceString = ss.str();
  const char *vertexShaderSource = vertexShaderSourceString.c_str();
  
  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
  }
  
  //fragment shader
  ifs = ifstream(fragmentShaderPath);
  ss.str("");
  ss << ifs.rdbuf();
  ifs.close();
  string fragmentShaderSourceString = ss.str();
  const char *fragmentShaderSource = fragmentShaderSourceString.c_str();
  
  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
  }
  
  
  GLuint shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  
  return shaderProgram;
}

void drawTriangle() {
}


int main(int argc, char * argv[]) {
  
  //glfw
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  
  GLFWwindow *window = glfwCreateWindow(640, 480, "hello modern opengl", nullptr, nullptr);
  if(window == nullptr){
    puts("failed to create glfw window");
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);
  
  //glew
  glewExperimental = true;
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
  GLuint shaderProgram = getShaderProgram("/Users/Terna/Desktop/playground-modern/playground-modern/vertex_shader.glsl", "/Users/Terna/Desktop/playground-modern/playground-modern/fragment_shader.glsl");
  
  GLfloat vertices[] = {
    -0.5,-0.5,0,
    0.5,-0.5,0,
    0,0.5,0
  };
  
  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  
  glBindVertexArray(VAO);
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
  }
  glBindVertexArray(0);
  
  while(!glfwWindowShouldClose(window)){
    glfwPollEvents();
    
    glClearColor(0.2, 0.3, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    {
      glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
  }
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  return 0;
}
