#pragma once

#include <glm.hpp>
#include <SFML/Graphics.hpp>

class GameObject
{
protected:
	// Logic
	glm::vec2 pos; // Position in pixel of the element.
	glm::uvec2 size; // Size in pixel

	// Graphics
	sf::Sprite* sprite;

public:
	GameObject();
	GameObject(const sf::Texture &);
	GameObject(glm::vec2, const sf::Texture &);
	GameObject(glm::vec2, glm::vec2, const sf::Texture &);
	virtual ~GameObject();

	sf::Sprite* getSprite();
	void setSprite(sf::Texture );
	void setSprite(sf::Texture, glm::uvec2);

	glm::vec2 getSize();

	glm::vec2 getPosition();
	void setPosition(glm::vec2);
};

