//
//  testResourceManager.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 3/5/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "ResourceManager.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "AppTestUtility.hpp"

int main(int argc, char * argv[])
{
  
  window = glGetWindow();
  
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  
  return RUN_ALL_TESTS();
}
