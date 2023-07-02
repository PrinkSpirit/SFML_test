#pragma once
#include "Actor.h"

class Pawn : public Actor
{
protected:
	glm::vec2 m_speed{1.0f,1.0f}; // Define acceleration on movement

public:
	Pawn();
	Pawn(glm::vec2 pos, const sf::Texture &texture);
	Pawn(glm::vec2 pos, glm::vec2 size, const sf::Texture &texture);
	virtual ~Pawn();

	//virtual void update() override;
	virtual void move(glm::vec2 dir);
};

