//
//  TextureMaterial.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/25/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include <glm/glm.hpp>
#include "TextureMaterial.hpp"

TextureMaterial::TextureMaterial() {
}

TextureMaterial::TextureMaterial(Texture diffuse, Texture specular, GLfloat shininess)
:	diffuse(diffuse),
	specular(specular),
	shininess(shininess){
};
