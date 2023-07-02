#pragma once
#include "Pawn.h"

class Player : public Pawn
{
	public:
	Player();
	Player(glm::vec2 pos, const sf::Texture& texture);
	Player(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture);
	virtual ~Player();

	//virtual void update() override;


};

