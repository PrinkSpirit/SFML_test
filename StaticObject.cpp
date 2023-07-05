#include <cstdlib>
#include <iostream>

#include "StaticObject.h"

unsigned int StaticObject::counter = 0;


StaticObject::StaticObject(glm::vec2 pos, const sf::Texture &texture, float isSolid) : 
	GameObject(pos, texture), isSolid(isSolid), id(counter++)
{
}

StaticObject::~StaticObject()
{

}


