#pragma once
#include "Pawn.h"
#include "Controller.h"

enum class PlayerState
{
	idle,
	movingLeft,
	movingRight,
	jumping,
	falling,
	crouching,
	attacking,
	hurt,
	dead
};

class Player : public Pawn
{
protected:
	bool m_jumping = false; /// Whether the player is jumping.
	bool m_grounded = false; /// Whether the player is on the ground.

	PlayerState m_state = PlayerState::idle; /// The current state of the player.

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


	void idle(float dT);
	void move(float dT);
	void attack(float dT);
	void crouch(float dT);

	/// <summary>
	/// Handle the jumping action.
	/// </summary>
	void jump(float dT);

	void fall(float dT);

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

