//
//  Material.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/24/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include <glm/glm.hpp>
#include "Material.hpp"

Material::Material() {
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shininess)
: ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	shininess(shininess){
};
