#pragma once

#include <vector>
#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Display.h"
#include "GameObject.h"


/// <summary>
/// Represent element that don't move like a wall or blocks.
/// </summary>
class StaticObject : public GameObject
{
protected:
	static unsigned int counter; // Counter of the number of StaticObject created. Unused.
	int id;						 // Id of the StaticObject. Unused.
	bool isSolid = true;		 // Whether the game should check for collision or not.

public:
	StaticObject() = delete;
	StaticObject(glm::vec2 pos, const sf::Texture &texture, float isSolid);
	StaticObject(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture, float isSolid);
	virtual ~StaticObject();
};