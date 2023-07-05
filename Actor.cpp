#include "Actor.h"

Actor::Actor() : GameObject()
{
}

Actor::Actor(glm::vec2 pos, const sf::Texture& texture) : GameObject(pos, texture)
{
	//this->sprite->setOrigin(texture.getSize().x / 16, texture.getSize().y / 16);
}

Actor::Actor(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture) : GameObject(pos, size, texture)
{
	//this->sprite->setOrigin(texture.getSize().x / 16, texture.getSize().y / 16);
}

Actor::~Actor()
{
}

glm::vec2 Actor::getVelocity() const
{
	return velocity;
}

void Actor::setVelocity(glm::vec2 velocity)
{
	this->velocity = velocity;
}

void Actor::addToVelocity(glm::vec2 velocity)
{
	this->velocity += velocity;
}

bool Actor::getGravity() const
{
	return gravity;
}

void Actor::update(float dT)
{
	velocity.y -= gravity * dT;

	position += velocity;

	velocity.x *= 0.0f;
}

