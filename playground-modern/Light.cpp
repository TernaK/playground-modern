//
//  Light.cpp
//  playground-modern
//
//  Created by Terna Kpamber on 2/25/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Light.hpp"

Light::Light(){
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position)
: ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	position(position){
}
