//
//  GLTextureNode.hpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/25/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef GLTextureNode_hpp
#define GLTextureNode_hpp

#include "GLNode.hpp"

class Texture {
private:
  
public:
  int n = 0;
  GLint texture;
  GLubyte* data = nullptr;
  
  Texture(){};
  
  Texture(GLubyte* data, int n) {
    this->data = new GLubyte[n];
    memcmp(this->data, data, n);
    this->n = n;
  }
  
  Texture(const Texture& from) {
    if(from.n > 0)
    	memcmp(this->data, from.data, n);
    this->n = from.n;
    this->texture = from.texture;
  }
  
  Texture& operator = (Texture from) {
    if(this != &from)
    *this = Texture(from);
    
    return *this;
  }
  
  ~Texture() {
    if(n > 0) delete [] data;
  }
};


class GLTextureNode : public GLNode  {
public:
  Texture texture;
  
  GLTextureNode();
};

#endif /* GLTextureNode_hpp */
