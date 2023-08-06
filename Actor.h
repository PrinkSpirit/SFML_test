#pragma once

#include "GameObject.h"
#include "Display.h"
#include "State.h"


/// @brief Represents elements that can move or be interacted with like hearts, doors, keys, etc.
class Actor : public GameObject
{
protected:
	glm::vec2 velocity{0.0f,0.0f};				///< Momentum of the actor
	glm::vec2 speedCap{ 200.0f,200.0f };		///< Maximum speed of the actor

	float gravity = .06f;						///< Gravity applied to the actor

	bool needUpdate = false;					///< Whether the actor need to be updated or not. Unused.
	float m_animTimer = 0.0f;					///< Timer used for animation

	std::map<std::string, State*> m_states;		///< Map of the states of the actor	
	State* m_state = nullptr;					///< Current state of the actor

public: 
	Actor();
	Actor(glm::vec2 pos, const sf::Texture &texture);
	Actor(glm::vec2 pos, glm::vec2 size, const sf::Texture &texture);
	virtual ~Actor();

	/// @brief Return the current velocity of the actor.
	/// @return glm vector 2 with velocity in 2 dimensions</returns>
	glm::vec2 getVelocity() const;


	/// @brief Set the velocity of the actor.
	/// @param velocity glm vector 2 with velocity in 2 dimensions
	void setVelocity(glm::vec2 velocity);
	
	/// @brief Add a vector to the current velocity
	/// @param velocity glm vector 2 with velocity in 2 dimensions
	void addToVelocity(glm::vec2 velocity);


	/// @brief Return the gravity applied to the actor.
	/// @return float gravity
	float getGravity();

	/// @brief Update the position of the actor according to its velocity and gravity.
	/// @param dT delta Time
	virtual void update(float dT);

	/// @brief Switch to the desired state.
	/// @param nextState Name of the next state.
	virtual void switchState(std::string nextState);
};

