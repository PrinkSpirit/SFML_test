#include "Actor.h"

Actor::Actor() : GameObject()
{
}

Actor::Actor(glm::vec2 pos, const sf::Texture& texture) : GameObject(pos, texture)
{
	//this->sprite->setOrigin(texture.getSize().x / 2.0, texture.getSize().y / 2.0);
}

Actor::Actor(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture) : GameObject(pos, size, texture)
{
	//this->sprite->setOrigin(texture.getSize().x / 2.0, texture.getSize().y / 2.0);
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

float Actor::getGravity()
{
	return gravity;
}

void Actor::update(float dT)
{
	velocity.y -= gravity * dT;

	position += velocity;


}

