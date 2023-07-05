#include "Pawn.h"

Pawn::Pawn() : Actor()
{
}

Pawn::Pawn(glm::vec2 pos, const sf::Texture& texture) : Actor(pos, texture)
{
}

Pawn::Pawn(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture) : Actor(pos, size, texture)
{
}

Pawn::~Pawn()
{
}

float Pawn::getAnimTimer() const
{
	return this->animTimer;
}


void Pawn::move(glm::vec2 dir)
{
	if (dir.x > 0) {
		this->velocity.x += this->m_speed.x;
	}
	else if (dir.x < 0) {
		this->velocity.x -= this->m_speed.x;
	}
	else {
		velocity.x = 0;
	}

	if (dir.y > 0) {
		this->velocity.y += this->m_speed.y;
	}
	else if (dir.y < 0) {
		this->velocity.y -= this->m_speed.y;
	}	
}

void Pawn::update(float dT)
{
	if (velocity.x > speedCap.x) {
		velocity.x = speedCap.x;
	}
	else if (velocity.x < -speedCap.x) {
		velocity.x = -speedCap.x;
	}

	if (velocity.y > speedCap.y) {
		velocity.y = speedCap.y;
	}
	else if (velocity.y < -speedCap.y) {
		velocity.y = -speedCap.y;
	}

	Actor::update(dT);
}
