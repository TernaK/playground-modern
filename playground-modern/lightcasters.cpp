//
//  playground-modern
//
//  Created by Terna Kpamber on 2/21/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Camera.hpp"
#include "Shader.hpp"
#include "GLTextureNode.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


Camera camera(glm::vec3(0,0,11.00));

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  
  if(key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GL_TRUE);
    return;
  }
  
  float d = 0.5;
  if(action == GLFW_REPEAT || action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_F: camera.eye.z -= d; break;
      case GLFW_KEY_B: camera.eye.z += d; break;
      case GLFW_KEY_LEFT: camera.eye.x -= d; break;
      case GLFW_KEY_RIGHT: camera.eye.x += d; break;
      case GLFW_KEY_UP: camera.eye.y += d; break;
      case GLFW_KEY_DOWN: camera.eye.y -= d; break;
        
      default:
        break;
    }
  }
  printf("camera position: [%.2f,%.2f,%.2f]\n", camera.eye.x, camera.eye.y, camera.eye.z);
}

int main(int argc, char * argv[]) {
  
  //glfw
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  GLFWwindow *window = glfwCreateWindow(600, 600, "hello modern opengl", nullptr, nullptr);
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
  
  //shader programs
  Shader shader("lighting_vertexshader.glsl","lighting_fragmentshader_objects.glsl");
  //  Shader lightShader("lighting_vertexshader.glsl","lighting_fragmentshader.glsl");
  
  vector<GLfloat> vertices = {
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
  };
  
  vector<GLuint> indices = {
    0,1,2, 3,2,1,//front
    5,4,7, 6,7,4,//back
    4,0,6, 2,6,0,//left
    1,5,3, 7,3,5,//rigt
    2,3,6, 7,6,3,//top
    4,5,0, 1,0,5//bottom
  };
  
  vector<GLfloat> normals = {
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    
   	-1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f
  };
  
  
  vector<GLfloat> texCoords = {
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0, //front
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0, //back
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0, //left
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0, //rigt
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0, //top
    0,1, 0,0, 1,1,  1,0, 1,1, 0,0 //bottom
  };
  
  glEnable(GL_DEPTH_TEST);
  
  Light light0 = Light(glm::vec3(0.7), glm::vec3(0.7), glm::vec3(0.03));
  light0.position = glm::vec3(5, 0, 0);
  light0.direction = glm::vec3(0, 0, 0.3f);
//  light0.diffuse = glm::vec3(0.7);
//  light0.ambient = glm::vec3(0.7);
//  light0.specular = glm::vec3(0.05);
  light0.type = LightType::POINT;
  
  TextureMaterial material = TextureMaterial(Texture("wood_diffuse.jpg"), Texture("wood_spec.jpg"), 0.5);
  
  vector<GLTextureNode> cubes;
  
  vector<glm::vec3> positions = {
    glm::vec3(0,0,0),
    glm::vec3(-3,0,0),
    glm::vec3(0,2,-4),
    glm::vec3(3,3,1),
    glm::vec3(1,-3,1),
  };
  
  vector<glm::vec3> scales;
  for(int i = 0 ; i < positions.size(); i++) {
    GLfloat scale = GLfloat(random()%100)*0.8/100.0f + 0.2;
    GLfloat rot = GLfloat(random()%100)/100.0f;
    scales.push_back(glm::vec3(scale));
    
    cubes.push_back(GLTextureNode(material, vertices, indices, normals, texCoords));
    cubes[i].position = positions[i];
    cubes[i].scale = scales[i];
    cubes[i].light = &light0;
    cubes[i].rotation = glm::vec3(rot*scale, scale, rot);
    cubes[i].init();
  }
  
  
  while(!glfwWindowShouldClose(window)){
    glfwPollEvents();
    
    glClearColor(0.15, 0.15, 0.15, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //camera
    camera.lookTowards(camera.eye, glm::vec3(0));
    camera.perspective(glm::radians(45.0f), GLfloat(width)/GLfloat(height), 0.1f, 50.0f);
    
    //cube
    shader.use();
    
    camera.setViewAndProjection(shader);
    glUniform3fv(glGetUniformLocation(shader.program, "eyePosition"), 1,  glm::value_ptr(camera.eye));
    
    for(vector<GLTextureNode>::iterator iter = cubes.begin(); iter != cubes.end(); iter++){
//      iter->rotation += glm::vec3(0, 0.01, 0);
      iter->draw(shader);
    }
    
    glfwSwapBuffers(window);
  }
  
  glfwTerminate();
  return 0;
}
