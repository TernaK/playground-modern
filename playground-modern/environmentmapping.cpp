//
//  environmentmapping.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 3/2/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>
#include "Shader.hpp"
#include "Camera.hpp"
#include "GLNode.hpp"
using namespace std;


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

GLuint loadSkybox(string root) {
  //texture
  string skyboxPath = root + "playground-modern/resources/skyboxes/mp_mandaris/mandaris_";
  vector<string> skyboxFiles
  {
    skyboxPath+"lf.jpg",
    skyboxPath+"rt.jpg",
   	skyboxPath+"up.jpg",
    skyboxPath+"dn.jpg",
    skyboxPath+"ft.jpg",
    skyboxPath+"bk.jpg",
  };
  
  GLuint skyboxTexture;
  glGenTextures(1, &skyboxTexture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
  glActiveTexture(GL_TEXTURE0);
  
  glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
  {
    for(int i = 0; i < skyboxFiles.size(); i++)
    {
      int tw, th;
      GLubyte *image = SOIL_load_image(skyboxFiles[i].c_str(), &tw, &th, 0, SOIL_LOAD_RGB);
      assert(image);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
      SOIL_free_image_data(image);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  }
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  
  return skyboxTexture;
}

GLuint loadObjectTexture() {
  GLuint texture1;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int tw, th;
  unsigned char *image1 = SOIL_load_image("texture2.jpg", &tw, &th, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image1);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  return texture1;
}

Light light;

int main()
{
  string root = string(SRC) + "/";
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  GLFWwindow *window = glfwCreateWindow(600, 600, "tutorial 1", nullptr, nullptr);
  if(window == NULL)
  {
    puts("could not create window");
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);
  
  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  
  // Options
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  
  glewExperimental = true;
  if(glewInit() != GLEW_OK)
  {
    puts("glew init failed");
    glfwTerminate();
    exit(-1);
  }
  
  GLint width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, GLsizei(width), GLsizei(height));
  //  glEnable(GL_DEPTH_TEST);
  
  /* cube */  vector<GLfloat> vertices = {
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
  GLNode cube = GLNode(vertices, indices, normals);
  cube.setMaterial(Material(glm::vec3(0.3,0.2,0.2), glm::vec3(0.3,0.3,0.3), glm::vec3(0.9), 256));
  cube.light = &light;
  cube.init();
  
//  
//  GLuint VAO, VBO;
//  glGenVertexArrays(1, &VAO);
//  glGenBuffers(1, &VBO);
//  
//  glBindVertexArray(VAO);
//  {
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    {
//      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.size(), data.data(), GL_STATIC_DRAW);
//      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
//      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
//      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));
//      glEnableVertexAttribArray(0);
//      glEnableVertexAttribArray(1);
//      glEnableVertexAttribArray(2);
//    }
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//  }
//  glBindVertexArray(0);
  
  
  /* skybox */
  vector<GLfloat> skyboxVertices = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
  };
  
  GLuint VAO_SKY, VBO_SKY;
  glGenVertexArrays(1, &VAO_SKY);
  glGenBuffers(1, &VBO_SKY);
  
  glBindVertexArray(VAO_SKY);
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO_SKY);
    {
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*skyboxVertices.size(), skyboxVertices.data(), GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
      glEnableVertexAttribArray(0);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  
  Shader shader(root+"playground-modern/environ_vertexshader.glsl", root+"playground-modern/lighting_fragmentshader_objects.glsl");
  Shader skyboxShader(root+"playground-modern/environmentmapping_vertexshader.glsl", root+"playground-modern/skybox_fragmentshader.glsl");
  
  /* skybox */
  GLuint skyboxTexture = loadSkybox(root);
  
  /* object */
//  GLuint objectTexture = loadObjectTexture();
  
  double lastTime = glfwGetTime();
  int nbFrames = 0;
//  GLfloat rotation = 0;
  
  while(!glfwWindowShouldClose(window))
  {
    // Measure speed
    double currentTime = glfwGetTime();
    nbFrames++;
    if ( currentTime - lastTime >= 2.0 ){ // If last prinf() was more than 1 sec ago
      // printf and reset timer
      printf("%.1f ms/frame\n", 2000.0/double(nbFrames));
      nbFrames = 0;
      lastTime += 2.0;
    }
    
    glfwPollEvents();
    
    glClearColor(0.1, 0.3, 0.4, 1.0);
    glEnable(GL_DEPTH_TEST);
    /*
     We render the skybox cleverly by setting it's depth value to 1.0 (the max).
     By doing this we can make sure to only render an object if it's depth is equal
     to OR LESS aka a finite value other than the maximum POSSIBLE.
     */
    
    /* render object */
    {
      glDepthFunc(GL_LESS);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      
      //cube
      shader.use();
      
      glUniform3fv(glGetUniformLocation(shader.program, "eyePosition"), 1,  glm::value_ptr(camera.position));
      
      //transformation
      glm::mat4 view = glm::lookAt(glm::vec3(0,0,5), glm::vec3(0,0,0), glm::vec3(0,1,0));
      glm::mat4 projection = glm::perspective(glm::radians(45.0f), GLfloat(width)/GLfloat(height), 0.1f, 100.0f);
      GLint viewLoc = glGetUniformLocation(shader.program, "view");
      GLint projectionLoc = glGetUniformLocation(shader.program, "projection");
      
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
      glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
      
//      glActiveTexture(GL_TEXTURE0);
//      glBindTexture(GL_TEXTURE_2D, objectTexture);
//      GLint textureLoc = glGetUniformLocation(shader.program, "textureMap");
//      glUniform1i(textureLoc, 0);
      
//      glBindVertexArray(VAO);
//      {
        cube.draw(shader);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//      }
//      glBindVertexArray(0);
    }
    /* render object end */
    
    /* render skybox */
//    {
//      glDepthFunc(GL_LEQUAL);
//      skyboxShader.use();
//      glm::mat4 view = glm::mat4( glm::mat3(camera.GetViewMatrix()) );
//      glm::mat4 projection = glm::perspective(glm::radians(45.0f), GLfloat(width)/GLfloat(height), 0.1f, 100.0f);
//      
//      GLint viewLoc = glGetUniformLocation(skyboxShader.program, "view");
//      GLint projectionLoc = glGetUniformLocation(skyboxShader.program, "projection");
//      
//      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//      glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//      
//      GLuint skyboxUniformLoc = glGetUniformLocation(skyboxShader.program, "skybox");
//      glUniform1f(skyboxUniformLoc, 0);
//      
//      glBindVertexArray(VAO_SKY);
//      {
//        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
//        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)skyboxVertices.size()/3);
//      }
//      glBindVertexArray(0);
//    }
    /* render skybox end */
    
    glfwSwapBuffers(window);
  }
  
  glDeleteTextures(1, &skyboxTexture);
//  glDeleteTextures(1, &objectTexture);
  glDeleteBuffers(1, &VBO_SKY);
  glDeleteVertexArrays(1, &VAO_SKY);
  glfwTerminate();
  exit(0);
}

// Moves/alters the camera positions based on user input
void Do_Movement()
{
  // Camera controls
  if(keys[GLFW_KEY_W])
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if(keys[GLFW_KEY_S])
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if(keys[GLFW_KEY_A])
    camera.ProcessKeyboard(LEFT, deltaTime);
  if(keys[GLFW_KEY_D])
    camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  
  if(action == GLFW_PRESS)
    keys[key] = true;
  else if(action == GLFW_RELEASE)
    keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if(firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }
  
  GLfloat xoffset = xpos - lastX;
  GLfloat yoffset = lastY - ypos;
  
  lastX = xpos;
  lastY = ypos;
  
  camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  camera.ProcessMouseScroll(yoffset);
}
