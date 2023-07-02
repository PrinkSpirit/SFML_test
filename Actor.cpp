#include "Actor.h"

Actor::Actor() : GameObject()
{
}

Actor::Actor(glm::vec2 pos, const sf::Texture& texture) : GameObject(pos, texture)
{
}

Actor::Actor(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture) : GameObject(pos, size, texture)
{
}

Actor::~Actor()
{
}

void Actor::update()
{
	if(usesGravity)
	{
		velocity.y -= gravity;
	}

	pos.x += velocity.x / 6;
	pos.y += velocity.y / 6;

	if (pos.y < 0)
	{
		pos.y = 0;
		velocity.y = 0;
	}
	velocity *= 0.9f;
}
