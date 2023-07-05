#pragma once
#include "GameObject.h"
#include "Display.h"



class Actor : public GameObject
{
protected:
	glm::vec2 velocity{0.0f,0.0f};
	glm::vec2 speedCap{ 200.0f,200.0f };

	float gravity = .06f;

	bool needUpdate = false;

public: 
	Actor();
	Actor(glm::vec2 pos, const sf::Texture &texture);
	Actor(glm::vec2 pos, glm::vec2 size, const sf::Texture &texture);
	virtual ~Actor();

	glm::vec2 getVelocity() const;
	void setVelocity(glm::vec2 velocity);
	
	void addToVelocity(glm::vec2 velocity);

	bool getGravity() const;

	virtual void update(float dT);
};

