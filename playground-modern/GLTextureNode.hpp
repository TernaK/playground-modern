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

class Texture{};

class GLTextureNode : public GLNode  {
public:
  Texture texture;
  
  GLTextureNode();
};

#endif /* GLTextureNode_hpp */
