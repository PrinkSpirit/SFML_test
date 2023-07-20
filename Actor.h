#pragma once
#include "GameObject.h"
#include "Display.h"


/// <summary>
/// Represents elements that can move or be interacted with like hearts, doors, keys, etc.
/// </summary>
class Actor : public GameObject
{
protected:
	glm::vec2 velocity{0.0f,0.0f};			// Momentum of the actor
	glm::vec2 speedCap{ 200.0f,200.0f };	// Maximum speed of the actor

	float gravity = .06f;					// Gravity applied to the actor

	bool needUpdate = false;				// Whether the actor need to be updated or not. Unused.
	float m_animTimer = 0.0f;					// Timer used for animation

	std::map<std::string, State*> states;

public: 
	Actor();
	Actor(glm::vec2 pos, const sf::Texture &texture);
	Actor(glm::vec2 pos, glm::vec2 size, const sf::Texture &texture);
	virtual ~Actor();

	/// <summary>
	/// Return the current velocity of the actor.
	/// </summary>
	/// <returns>gml vector 2 with velocity in 2 dimensions</returns>
	glm::vec2 getVelocity() const;

	/// <summary>
	/// Set the velocity of the actor.
	/// </summary>
	/// <param name="velocity">gml vector 2 with velocity in 2 dimensions</param>
	void setVelocity(glm::vec2 velocity);
	
	/// <summary>
	/// Add a vector to the current velocity
	/// </summary>
	/// <param name="velocity">gml vector 2 with velocity in 2 dimensions</param>
	void addToVelocity(glm::vec2 velocity);

	/// <summary>
	/// Return the gravity applied to the actor.
	/// </summary>
	/// <returns>float gravity</returns>
	float getGravity();

	/// <summary>
	/// Update the position of the actor according to its velocity and gravity.
	/// </summary>
	/// <param name="dT">delta Time</param>
	virtual void update(float dT);

	virtual void switchState(std::string nextState);
};

