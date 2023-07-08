#pragma once

#include <glm.hpp>
#include <SFML/Graphics.hpp>

/// <summary>
/// Virtual class serving as a base for any element in game.
/// </summary>
class GameObject
{
protected:
	// Logic
	glm::vec2 position; // Position in pixel of the element.
	glm::uvec2 size; // Size in pixel

	// Graphics
	sf::Sprite* sprite; // Sprite of the element

public:
	GameObject();
	GameObject(const sf::Texture &);
	GameObject(glm::vec2, const sf::Texture &);
	GameObject(glm::vec2, glm::vec2, const sf::Texture &);

	/// <summary>
	/// Destructor of the class. Delete the following:
	/// - sprite
	/// </summary>
	virtual ~GameObject();

	/// <summary>
	/// Return a point to the sprite of the element.
	/// </summary>
	/// <returns>Point to the sf::Sprite</returns>
	sf::Sprite* getSprite();

	/// <summary>
	/// Set the texture of the sprite of the element.
	/// </summary>
	/// <param name="texture">Texture to be set</param>
	void setSprite(sf::Texture);
	/// <summary>
	/// Set the texture of the sprite of the element as well as it's size.
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	void setSprite(sf::Texture, glm::uvec2);

	glm::vec2 getSize();

	glm::vec2 getPosition();
	void setPosition(glm::vec2);
};

