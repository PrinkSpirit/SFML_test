#include <cstdlib>
#include <iostream>

#include "StaticObject.h"

unsigned int StaticObject::counter = 0;


StaticObject::StaticObject(glm::vec2 pos, const sf::Texture &texture, float isSolid) : 
	GameObject(pos, texture), isSolid(isSolid), id(counter++)
{
}

StaticObject::StaticObject(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture, float isSolid) :
	GameObject(pos, size, texture), isSolid(isSolid), id(counter++)
{
}

StaticObject::~StaticObject()
{

}


