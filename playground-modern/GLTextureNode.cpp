//
//  GLTextureNode.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/25/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "GLTextureNode.hpp"
using namespace std;

GLTextureNode::GLTextureNode() {
}

GLTextureNode::GLTextureNode(TextureMaterial material, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals, const std::vector<GLfloat>& texCoords)
:	GLNode(vertices, indices, normals),
	texCoords(texCoords) {
  this->material = material;
}

//GLTextureNode::GLTextureNode(Texture texture, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals)
//:GLNode(vertices, indices, normals) {
//  this->material.texture = texture;
//}

GLTextureNode::GLTextureNode(std::string image, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals, const std::vector<GLfloat>& texCoords)
:	GLNode(vertices, indices, normals),
	texCoords(texCoords) {
  this->material = TextureMaterial(Texture(image), Texture(image), 32);
}

void GLTextureNode::init() {
  material.diffuse.init();
  material.specular.init();
  assert(material.diffuse.ready && material.specular.ready);
  
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  
  //concatenate vertex normal and texture coordinate data (vcn)
  vector<GLfloat> vertNorTex;// = vertices;
  for(auto index: indices) {
    vertNorTex.push_back(vertices[index * 3]);
    vertNorTex.push_back(vertices[index * 3 + 1]);
    vertNorTex.push_back(vertices[index * 3 +2]);
  }
  
//  if(!normals.empty())
  vertNorTex.insert(vertNorTex.end(), normals.begin(), normals.end());
  
  vertNorTex.insert(vertNorTex.end(), texCoords.begin(), texCoords.end());
  
  //convert vcn to c array
  GLfloat verticesNormalTexArray[vertNorTex.size()];
  for(int i = 0 ; i < vertNorTex.size(); i++)
    verticesNormalTexArray[i] = vertNorTex[i];
  
  //offsets in the vcn array
  auto normalsOffset = 3 * sizeof(GLfloat) * indices.size();
  auto textureOffset = normalsOffset + normals.size() * sizeof(GLfloat);
  
  glBindVertexArray(VAO);
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesNormalTexArray), verticesNormalTexArray, GL_STATIC_DRAW);
    
    //vertives
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)normalsOffset);
    glEnableVertexAttribArray(1);
    
    //texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid*)textureOffset);
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  ready = true;
}

void GLTextureNode::draw(Shader shader) {
  
  assert(ready && material.diffuse.ready && material.specular.ready);
  
  //model
  model = glm::translate(glm::mat4(1.0f), position);
  model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, scale);
  glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  
  //material
  GLint matDiffuseLoc  = glGetUniformLocation(shader.program, "material.diffuse");
  GLint matSpecularLoc = glGetUniformLocation(shader.program, "material.specular");
  GLint matShineLoc    = glGetUniformLocation(shader.program, "material.shininess");
  
  //texture
  material.diffuse.activate(shader, 0);
  glUniform1i(matDiffuseLoc, 0);
  
  material.specular.activate(shader, 1);
  glUniform1i(matSpecularLoc, 1);
  
  glUniform1f(matShineLoc, material.shininess);
  
  //light
  GLint lightAmbientLoc  	= glGetUniformLocation(shader.program, "light.ambient");
  GLint lightDiffuseLoc  	= glGetUniformLocation(shader.program, "light.diffuse");
  GLint lightSpecularLoc 	= glGetUniformLocation(shader.program, "light.specular");
  GLint lightPositionLoc 	= glGetUniformLocation(shader.program, "light.position");
  GLint lightDirectionLoc = glGetUniformLocation(shader.program, "light.direction");
  GLint lightTypeLoc 			= glGetUniformLocation(shader.program, "light.type");
  
  glUniform3fv(lightAmbientLoc, 1, glm::value_ptr(light->ambient));
  glUniform3fv(lightDiffuseLoc, 1, glm::value_ptr(light->diffuse));
  glUniform3fv(lightSpecularLoc, 1, glm::value_ptr(light->specular));
  glUniform3fv(lightPositionLoc, 1, glm::value_ptr(light->position));
  glUniform3fv(lightDirectionLoc, 1, glm::value_ptr(light->direction));
  glUniform1i(lightTypeLoc, light->type);
  
  glBindVertexArray(VAO);
  {
    glDrawArrays(GL_TRIANGLES, 0, GLint(indices.size()));
  }
  glBindVertexArray(0);
}
