#pragma once

#include <vector>
#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Display.h"
#include "GameObject.h"


enum class BlockType {
	Brick,
};

class StaticObject : public GameObject
{
protected:
	static unsigned int counter;
	int id;
	bool isSolid = true;

public:
	StaticObject() = delete;
	StaticObject(glm::vec2 pos, const sf::Texture &texture, float isSolid);
	virtual ~StaticObject();
};