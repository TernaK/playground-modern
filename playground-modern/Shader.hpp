//
//  Shader.hpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/22/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader
{
public:
  /* methods */
  Shader(){};
  
  // create shader using file paths
  Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
  
  // generate shader using sources
  static Shader ShaderFromSources(std::string vertexShaderSource, std::string fragmentShaderSource);
  
  // use shader
  const Shader& use();
  
  /* members */
  GLuint program = 0;
  
private:
  // helper method for creating shader
  static GLuint createShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource);
};

#endif /* Shader_hpp */
