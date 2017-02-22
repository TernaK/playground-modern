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

class Shader {
public:
  GLuint program;
  Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
  void use();
};

#endif /* Shader_hpp */
