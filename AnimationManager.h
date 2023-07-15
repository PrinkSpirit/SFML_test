#pragma once

#include <map>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "GameObject.h"


/// <summary>
/// Keep a map with all the animations.
/// Name -> number
/// </summary>
class AnimationManager : GameObject
{
protected:
	std::map<std::string, std::vector<sf::IntRect>> m_animations;

	bool looping = false;
	float m_animationTimer = 0.0f;

public:
	void addSequence(std::string name, std::vector<sf::IntRect> sequence);
	void setSprite(sf::Sprite* sprite);
	void getSprite(sf::Sprite* sprite);
	void setSize(sf::Vector2i size);

	void resetAnimation();
	void setAnimation(std::string name);

	void play(std::string name, float deltaTime, bool loop = false);
	void update(float deltaTime);

};

