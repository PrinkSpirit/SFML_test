#pragma once
#include "GameObject.h"


class Actor : public GameObject
{
protected:
	glm::vec2 velocity{0.0f,0.0f};

	float gravity = 0.2f;

	bool usesGravity = true;
	bool needUpdate = false;

public:
	Actor();
	Actor(glm::vec2 pos, const sf::Texture &texture);
	Actor(glm::vec2 pos, glm::vec2 size, const sf::Texture &texture);
	virtual ~Actor();

	virtual void update();
};

