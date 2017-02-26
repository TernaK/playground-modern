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

TextureMaterial::TextureMaterial(Texture texture, glm::vec3 specular, GLfloat shininess)
:	texture(texture),
	specular(specular),
	shininess(shininess){
};
