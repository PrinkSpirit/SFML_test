#include "GameObject.h"

#include <iostream>

GameObject::GameObject()
{
	this->pos = glm::vec2(0, 0);
	this->size = glm::uvec2(0, 0);

	this->sprite = new sf::Sprite();
}

GameObject::GameObject(const sf::Texture &texture)
{
	this->pos = glm::vec2(0, 0);
	this->sprite = new sf::Sprite();

	this->sprite->setTexture(texture);
	this->size = glm::uvec2(texture.getSize().x, texture.getSize().y);
}

GameObject::GameObject(glm::vec2 pos, const sf::Texture &texture) :  pos(pos)
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(texture);
	this->size = glm::uvec2(texture.getSize().x, texture.getSize().y);
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, const sf::Texture &texture) : pos{ pos }, size{ size }
{
	this->sprite->setTexture(texture);
}

GameObject::~GameObject()
{
	delete this->sprite;
}


/* -------------------------------------------------- */


sf::Sprite* GameObject::getSprite()
{
	return this->sprite;
}

void GameObject::setSprite(sf::Texture texture)
{
	this->sprite->setTexture(texture);
}

void GameObject::setSprite(sf::Texture texture, glm::uvec2 size)
{
	this->sprite->setTexture(texture);
	this->size = size;
}

glm::vec2 GameObject::getSize()
{
	return this->size;
}

glm::vec2 GameObject::getPosition()
{
	return this->pos;
}

void GameObject::setPosition(glm::vec2 pos)
{
	this->pos = pos;
}
