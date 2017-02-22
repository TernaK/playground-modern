//
//  Shader.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/22/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Shader.hpp"
using namespace std;
Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
  ifstream ifs;
  stringstream ss;
  GLint success;
  GLchar infoLog[512];
  
  //vertex shader
  ifs = ifstream(vertexShaderPath);
  if(!ifs.is_open()){
    puts("ERROR::SHADER::could not find vertex shader");
    exit(-1);
  }
  
  ss << ifs.rdbuf();
  const GLchar *vertexShaderStr = ss.str().c_str();
  
  GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderStr, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::compilation failed\n" << infoLog << std::endl;
    exit(-1);
  }
  ifs.close();
  
  //fragment shader
  ifs = ifstream(fragmentShaderPath);
  if(!ifs.is_open()){
    puts("ERROR::SHADER::could not find vertex shader");
    exit(-1);
  }
  ss.str("");
  ss << ifs.rdbuf();
  const GLchar *fragmentShaderStr = ss.str().c_str();
  
  GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderStr, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::compilation failed\n" << infoLog << std::endl;
    exit(-1);
  }
  
  //shader program
  this->program = glCreateProgram();
  glAttachShader(this->program, vertexShader);
  glAttachShader(this->program, fragmentShader);
  glLinkProgram(this->program);
  glGetProgramiv(this->program, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(this->program, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::linking failed\n" << infoLog << std::endl;
    exit(-1);
  }
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  ifs.close();
}

void Shader::use(){
  glUseProgram(this->program);
}
