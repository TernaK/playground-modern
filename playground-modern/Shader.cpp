//
//  Shader.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/22/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Shader.hpp"
using namespace std;

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
  ifstream ifs;
  stringstream ss;
  string fileText;
  
  // vertex shader
  ifs = ifstream(vertexShaderPath);
  if(!ifs.is_open()){
    puts("ERROR::SHADER::could not find vertex shader");
    exit(-1);
  }
  ss << ifs.rdbuf();
//  string vSring = ss.str();
  string vertexShaderStr = ss.str();//.c_str();
  ifs.close();
  
  // fragment shader
  ifs = ifstream(fragmentShaderPath);
  if(!ifs.is_open()){
    puts("ERROR::SHADER::could not find fragment shader");
    exit(-1);
  }
  ss.str("");//clear string
  ss << ifs.rdbuf();
//  fileText = ss.str();
  string fragmentShaderStr = ss.str();
  
  // create shader
  this->program = createShaderProgram(vertexShaderStr, fragmentShaderStr);
  
  ifs.close();
}

Shader Shader::ShaderFromSources(std::string vertexShaderSource, std::string fragmentShaderSource)
{
  Shader s;
  s.program = createShaderProgram(vertexShaderSource, fragmentShaderSource);
  return s;
}

GLuint Shader::createShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource)
{
  GLint success;
  GLchar infoLog[512];
  
  const GLchar *vertex_src = vertexShaderSource.c_str();
  const GLchar *fragment_src = fragmentShaderSource.c_str();
  
  GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_src, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::compilation failed\n" << infoLog << std::endl;
    exit(-1);
  }
  
  GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragment_src, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::compilation failed\n" << infoLog << std::endl;
    exit(-1);
  }
  
  //shader program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::linking failed\n" << infoLog << std::endl;
    exit(-1);
  }
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  
  return shaderProgram;
}

const Shader& Shader::use() const
{
  glUseProgram(this->program);
  return *this;
}


void Shader::setFloat(std::string name, GLfloat value, GLboolean useShader) const
{
  if(useShader) this->use();
  GLint loc = glGetUniformLocation(this->program, name.c_str());
  glUniform1f(loc, value);
}

void Shader::setInteger(std::string name, GLint value, GLboolean useShader) const
{
  if(useShader) this->use();
  GLint loc = glGetUniformLocation(this->program, name.c_str());
  glUniform1i(loc, value);
}

void Shader::setVector2f(std::string name, const glm::vec2 &value, GLboolean useShader) const
{
  if(useShader) this->use();
  GLint loc = glGetUniformLocation(this->program, name.c_str());
  glUniform2fv(loc, 1, value_ptr(value));
}

void Shader::setVector3f(std::string name, const glm::vec3 &value, GLboolean useShader) const
{
  if(useShader) this->use();
  GLint loc = glGetUniformLocation(this->program, name.c_str());
  glUniform3fv(loc, 1, value_ptr(value));
}

void Shader::setVector4f(std::string name, const glm::vec4 &value, GLboolean useShader) const
{
  if(useShader) this->use();
  GLint loc = glGetUniformLocation(this->program, name.c_str());
  glUniform4fv(loc, 1, value_ptr(value));
}

void Shader::setMatrix4(std::string name, const glm::mat4 &matrix, GLboolean useShader) const
{
  if(useShader) this->use();
  GLint loc = glGetUniformLocation(this->program, name.c_str());
  glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(matrix));
}
