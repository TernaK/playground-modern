//
//  Texture.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/25/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Texture.hpp"
using namespace std;

Texture::Texture(){
  
};

Texture::Texture(GLubyte* data, int width, int height, int channels) {
  assert(width * height * channels > 0);
  assign(data, width, height, channels);
}

Texture::Texture(std::string imageFile) {
  int width, height, channels;
  GLubyte *image = SOIL_load_image(imageFile.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
  if(!image){
    cout << "ERROR::CALSS::TEXTURE:: could not open " << imageFile << endl;
    exit(-1);
  }
  assign(image, width, height, channels);
  SOIL_free_image_data(image);
}

Texture& Texture::operator = (Texture from) {
  if(this->data != nullptr) delete [] data;
  if(this != &from) {
    assign(from.data, from.width, from.height, from.channels);
    this->ready = from.ready;
    this->texture = from.texture;
  }
  
  return *this;
}

Texture::Texture(const Texture& from) {
  if(this->data != nullptr) delete [] data;
  if(from.width*from.height*from.channels > 0){
    assign(from.data, from.width, from.height, from.channels);
    this->ready = from.ready;
    this->texture = from.texture;
  }
}

Texture::~Texture() {
  if(width*height*channels > 0) {
    delete [] data;
    data = nullptr;
  }
}

void Texture::assign(GLubyte* data, int width, int height, int channels) {
  assert(width * height * channels > 0);
  this->data = new GLubyte[width*height*channels];
  memcpy(this->data, data, width*height*channels);
  this->width = width;
  this->height = height;
  this->channels = channels;
}

void Texture::init() {
  assert(width * height * channels > 0);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  ready = true;
};

void Texture::activate(Shader shader) {
  assert(ready);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
}
