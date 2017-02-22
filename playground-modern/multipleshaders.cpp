//
//  playground-modern
//
//  Created by Terna Kpamber on 2/21/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

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

const char *vertexShaderString =
"	#version 330 core\n"
" layout (location = 0) in vec3 position;\n"
" void main() {\n"
"  gl_Position = vec4(position, 1.0);\n"
" }" ;

const char *fragmentShader1String =
"	#version 330 core\n"
" out vec3 color;\n"
" void main() {\n"
"  color = vec3(1.0, 0.5, 0.2);\n"
" }" ;

const char *fragmentShader2String =
"	#version 330 core\n"
" out vec3 color;\n"
" void main() {\n"
"  color = vec3(0.5, 1.0, 0.2);\n"
" }" ;

vector<GLint> getShaderPrograms() {
  vector<GLint> shaderPrograms;
  
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderString, NULL);
  glCompileShader(vertexShader);
  
  GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader1, 1, &fragmentShader1String, NULL);
  glCompileShader(fragmentShader1);
  
  GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader2, 1, &fragmentShader2String, NULL);
  glCompileShader(fragmentShader2);
  
  GLint shaderProgram1 = glCreateProgram();
  glAttachShader(shaderProgram1, vertexShader);
  glAttachShader(shaderProgram1, fragmentShader1);
  glLinkProgram(shaderProgram1);
  shaderPrograms.push_back(shaderProgram1);
  
  GLint shaderProgram2 = glCreateProgram();
  glAttachShader(shaderProgram2, vertexShader);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram2);
  shaderPrograms.push_back(shaderProgram2);
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader1);
  
  return shaderPrograms;
  
	//  GLint success;
  //  GLchar infoLog[512];
  //  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  //  if(!success) {
  //    glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
  //    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  //  }
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
  vector<GLint> shaderPrograms = getShaderPrograms();
  
  GLfloat vertices[] = {
    -0.5,-0.5,0,
    0.5,-0.5,0,
    -0.5,0.5,0,
    0.5,0.5,0
  };
  GLuint indices[] = {
    0,1,2,
    1,2,3
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  
  while(!glfwWindowShouldClose(window)){
    glfwPollEvents();
    
    glClearColor(0.3, 0.4, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderPrograms[0]);
    glBindVertexArray(VAO);
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid *)0);
    }
    glBindVertexArray(0);
    
    glUseProgram(shaderPrograms[1]);
    glBindVertexArray(VAO);
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid *)(3*sizeof(GLint)));
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
