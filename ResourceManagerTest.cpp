//
//  testResourceManager.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 3/5/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Texture.hpp"
#include "Shader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>
using namespace std;

GLFWwindow* glSetup(void);

GLFWwindow *window;

TEST(ShaderTest, TestInitialization)
{
  Shader s("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
  ASSERT_GT(s.program, 0);
}

TEST(TextureTest, TestInitialization)
{
  Texture t("resources/textures/awesomeface.png");
  ASSERT_GT(t.textureId, 0);
}

int main(int argc, char * argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  
  window = glSetup();
  
  return RUN_ALL_TESTS();
}

GLFWwindow* glSetup()
{
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
  
  return window;
}


