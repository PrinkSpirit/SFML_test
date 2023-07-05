#pragma once
#include "Pawn.h"
#include "Controller.h"

class Player : public Pawn
{
protected:
	bool m_jumping = false;
	bool grounded = false;

	Controller* m_controller = nullptr;
	std::vector< sf::IntRect > m_animations;

public:
	Player();
	Player(glm::vec2 pos, const sf::Texture& texture);
	Player(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture);
	virtual ~Player();

	bool isJumping() const;
	void jump();
	//virtual void move(int input);
	virtual void update(float dT) override;

	void setController(Controller* controller);
	Controller* getController() const;
};

