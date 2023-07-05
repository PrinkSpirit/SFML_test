#pragma once
#include "Actor.h"

enum class State
{
	iddle,
	movingLeft,
	movingRight,
	jumping,
	attacking
};

class Pawn : public Actor
{
protected:
	glm::vec2 m_speed{1.0f,1.0f}; // Define acceleration on movement
	State state = State::iddle;
	float animTimer = 0.0f;

public:
	Pawn();
	Pawn(glm::vec2 pos, const sf::Texture &texture);
	Pawn(glm::vec2 pos, glm::vec2 size, const sf::Texture &texture);
	virtual ~Pawn();

	float getAnimTimer() const;

	virtual void update(float dT) override;
	virtual void move(glm::vec2 dir);
};

