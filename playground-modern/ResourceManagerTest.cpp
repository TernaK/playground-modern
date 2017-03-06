//
//  testResourceManager.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 3/5/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "ResourceManager.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>
using namespace std;

GLFWwindow* glSetup(void);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

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

TEST(ResourceManagerTest, TestInitialization)
{
  Shader s("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
  Texture t("resources/textures/awesomeface.png");
  
  ResourceManager rm;
  
  // catch non-existent shaders
  rm.addShader(s, "shader");
  rm.addTexture(t, "texture");
  ASSERT_GT(rm.getShader("shader").program, 0);
  ASSERT_EQ(rm.getShader("texture").program, 0);
  ASSERT_GT(rm.getTexture("texture").textureId, 0);
  ASSERT_EQ(rm.getTexture("shader").textureId, 0);
  
  // catch duplicate shaders
  rm.addShader(s, "shader");
  rm.addTexture(t, "texture");
  ASSERT_EQ(rm.shaders.size(), 1);
  ASSERT_EQ(rm.textures.size(), 1);
}

int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  
  window = glSetup();
  
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  
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
  
  return window;
}
