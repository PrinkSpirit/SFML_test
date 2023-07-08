#pragma once
#include "Pawn.h"
#include "Controller.h"

class Player : public Pawn
{
protected:
	bool m_jumping = false; /// Whether the player is jumping.
	bool grounded = false; /// Whether the player is on the ground.

	Controller* m_controller = nullptr;			/// Pointer to the control manager
	std::vector< sf::IntRect > m_animations;    /// Vector of the sprites for the animation

public:
	Player();
	Player(glm::vec2 pos, const sf::Texture& texture);
	Player(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture);
	virtual ~Player();

	/// <summary>
	/// Return whether the player is jumping or not.
	/// </summary>
	/// <returns>boolean of the jumping state</returns>
	bool isJumping() const;

	/// <summary>
	/// Handle the jumping action.
	/// </summary>
	void jump();

	//virtual void move(int input);

	/// <summary>
	/// Update the player state.
	/// Call the actor parent update function.
	/// </summary>
	/// <param name="dT">Delta Time</param>
	virtual void update(float dT) override;

	/// <summary>
	/// Set the pointer to the control manager.
	/// </summary>
	/// <param name="controller">Pointer to controller</param>
	void setController(Controller* controller);

	/// <summary>
	/// Return the pointer to the control manager.
	/// </summary>
	/// <returns>Pointer to controller</returns>
	Controller* getController() const;
};

