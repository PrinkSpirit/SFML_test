#pragma once
#include "Pawn.h"
#include "Controller.h"
#include "State.h"

/// @brief Player class.
class Player : public Pawn
{
protected:
	bool m_jumping = false; /// Whether the player is jumping.
	bool m_grounded = false; /// Whether the player is on the ground.

	Controller* m_controller = nullptr;			/// Pointer to the control manager

	// Player states
	class PlayerState;	// Abstract base class for other states
	class Idle;			// Idle state
	class Walk;			// Walking state
	class Jump;			// Jumping state
	class Crouch;		// Crouching state
	class Attack;		// Attacking state
	class CrouchStab;	// Crouch attack state

	// State decorators
	template <class T>
	class CanFall;		// Allow state to handle gravity
	template <class T>
	class CanMove;		// Allow state to handle horizontal movement
	template <class T>
	class CanJump;		// Allow state to switch to jumping state via the jump action
	template <class T>
	class CanWalk;		// Allow state to switch to walking state via grounded movement
	template <class T>
	class CanCrouch;	// Allow state to switch to crouching state via the down action
	template <class T>
	class CanAttack;	// Allow state to switch to attacking state via the attack action


public:
	Player();
	Player(glm::vec2 pos, const sf::Texture& texture);
	//Player(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture);
	virtual ~Player();
	
	/// @brief Update the player state. Call the actor parent update function.
	/// @param dT Delta Time
	virtual void update(float dT) override;

	/// @brief Set the pointer to the control manager.	
	/// @param dT Pointer to controller
	void setController(Controller* controller);


	/// @brief Return the pointer to the control manager.
	/// @returns Pointer to controller
	Controller* getController() const;
};


/* ********** ********** ********** ********** ********** */
/*							STATES	                      */
/* ********** ********** ********** ********** ********** */

/// @brief State base class for players. Abstract.
class Player::PlayerState : public State {
protected:
	/// @brief Pointer to the player.
	Player* m_player;

public:
	PlayerState() = delete;
	PlayerState(Player*);
	virtual ~PlayerState();

	void in(float dT) override = 0;
	void out(float dT) override = 0;
	void update(float dT) override = 0;

	//virtual void jump(float) = 0;
	//virtual void croutch(float) = 0;
};


/// @brief Basic state for imobile player.
class Player::Idle : public PlayerState {
protected:
	sf::IntRect m_spriteRect;

public:
	void in(float dT);
	void out(float dT);
	void update(float dT);

	Idle(Player*);
	~Idle();
};

/// @brief Walking on the ground.
class Player::Walk : public PlayerState {
protected:
	std::vector<sf::IntRect> m_animationSequence;
	float m_animationTimer = 0.0f;

public:
	void in(float dT);
	void out(float dT);
	void update(float dT);

	Walk(Player*);
	~Walk();
};

/// @brief Jumping state.
class Player::Jump : public PlayerState {
protected:
	sf::IntRect m_spriteRect;

	bool m_jumpHeld = false;
	float m_jumpHeldTimer;
	float m_jumpMaxDuration;

public:
	void in(float dT);
	void out(float dT);
	void update(float dT);

	Jump(Player*);
	~Jump();
};

/// @brief Crouched state.
class Player::Crouch : public PlayerState {
protected:
	sf::IntRect m_spriteRect;

public:
	void in(float dT);
	void out(float dT);
	void update(float dT);

	Crouch(Player*);
	~Crouch();
};

/// @brief Attacking state.
class Player::Attack : public PlayerState {
protected:
	std::vector<sf::IntRect> m_animationSequence;
	float m_animationTimer = 0.0f;

public:
	void in(float dT);
	void out(float dT);
	void update(float dT);

	Attack(Player*);
	~Attack();
};

class Player::CrouchStab : public PlayerState {
protected:
	std::vector<sf::IntRect> m_animationSequence;
	float m_animationTimer = 0.0f;

public:
	void in(float dT);
	void out(float dT);
	void update(float dT);

	CrouchStab(Player*);
	~CrouchStab();
};

/* ********** ********** ********** ********** ********** */
/*                     STATES DECORATOR                   */
/* ********** ********** ********** ********** ********** */

/// @brief'Handle horizontal movement for the current state. Décorator.
/// @tparam T Child of PlayerState
template <class T>
class Player::CanMove : public T {
	static_assert(std::is_base_of<Player::PlayerState, T>::value, "Target State must derive from PlayerState");
	sf::Vector2f m_scale;

public:
	void in(float dT) {
		T::in(dT);
	}

	void out(float dT) {
		T::out(dT);
	}

	void update(float dT) {
		if (T::m_player->getController()->left())
			T::m_player->velocity.x -= T::m_player->m_speed.x * dT;
		if (T::m_player->getController()->right())
			T::m_player->velocity.x += T::m_player->m_speed.x * dT;

		if (T::m_player->velocity.x > T::m_player->speedCap.x) {
			T::m_player->velocity.x = T::m_player->speedCap.x;
		}
		else if (T::m_player->velocity.x < -T::m_player->speedCap.x) {
			T::m_player->velocity.x = -T::m_player->speedCap.x;
		}

		if (T::m_player->velocity.x < -FLT_EPSILON) {
			T::m_player->sprite->setScale(-4, 4);
		}
		else if (T::m_player->velocity.x > FLT_EPSILON) {
			T::m_player->sprite->setScale(4, 4);
		}

		T::update(dT);
	}

	// Allow transfer of arguments to the constructor of the decorated state to next in line.
	template <typename... Args>
	CanMove(Args... args) : T(std::forward<Args>(args)...) {}

	~CanMove() {}
};

/// @brief Handle gravity for the current state. Indicate that the player can fall. Décorator.
/// @tparam T Child of PlayerState
template <class T>
class Player::CanFall : public T {
	static_assert(std::is_base_of<Player::PlayerState, T>::value, "T must derive from PlayerState");

public:
	void in(float dT) {
		T::in(dT);
	}

	void out(float dT) {
		T::out(dT);
	}

	void update(float dT) {
		T::update(dT);

		if (!T::m_player->m_jumping) {
			T::m_player->velocity.y -= T::m_player->gravity * dT;
		}
	}

	// Allow transfer of arguments to the constructor of the decorated state to next in line.
	template <typename... Args>
	CanFall(Args... args) : T(std::forward<Args>(args)...) {}

	~CanFall() {}
};

/* -------- State Switchers ---------- */

/// @brief Handle the jumping action in the decorated state. Décorator.
/// @tparam T Child of PlayerState
template <class T>
class Player::CanJump : public T {
	static_assert(std::is_base_of<Player::PlayerState, T>::value, "T must derive from PlayerState");

public:
	void in(float dT) {
		T::in(dT);
	}

	void out(float dT) {
		T::out(dT);
	}

	void update(float dT) {
		//T::m_player->m_grounded && 
		if (T::m_player->getController()->jump()) {
			T::m_player->switchState("Jump");
			return; // Return on state change
		}
			
		T::update(dT);
	}

	// Allow transfer of arguments to the constructor of the decorated state to next in line.
	template <typename... Args>
	CanJump(Args... args) : T(std::forward<Args>(args)...) {}

	~CanJump() {}
};



/// @brief Check for left and right actions while grounded. Décorator.
/// @tparam T Child of PlayerState
template <class T>
class Player::CanWalk : public T {
	static_assert(std::is_base_of<Player::PlayerState, T>::value, "T must derive from PlayerState");

public:
	void in(float dT) {
		T::in(dT);
	}

	void out(float dT) {
		T::out(dT);
	}

	void update(float dT) {
		//T::m_player->m_grounded && 
		if ((T::m_player->velocity.x < -FLT_EPSILON || T::m_player->velocity.x > FLT_EPSILON)) {
			T::m_player->switchState("Walk");
			return; // Return on state change
		}
		T::update(dT);
	}

	// Allow transfer of arguments to the constructor of the decorated state to next in line.
	template <typename... Args>
	CanWalk(Args... args) : T(std::forward<Args>(args)...) {}
};

/// @brief Handle switching to the crouch state. Décorator.
/// @tparam T Child of PlayerState
template <class T>
class Player::CanCrouch : public T { 
	static_assert(std::is_base_of<Player::PlayerState, T>::value, "T must derive from PlayerState");

public:
	void in(float dT) {
		T::in(dT);
	}

	void out(float dT) {
		T::out(dT);
	}

	void update(float dT) {
		if (T::m_player->getController()->down()) {
			T::m_player->switchState("Crouch");
			return; // Return on state change
		}
		T::update(dT);
	}

	// Allow transfer of arguments to the constructor of the decorated state to next in line.
	template <typename... Args>
	CanCrouch(Args... args) : T(std::forward<Args>(args)...) {}
};

// can attack
template <class T>
class Player::CanAttack : public T {
	static_assert(std::is_base_of<Player::PlayerState, T>::value, "T must derive from PlayerState");

public:
	void in(float dT) {
		T::in(dT);
	}

	void out(float dT) {
		T::out(dT);
	}

	void update(float dT) {
		if (T::m_player->getController()->attack()) {
			T::m_player->switchState("Attack");
			return; // Return on state change
		}
		T::update(dT);
	}

	// Allow transfer of arguments to the constructor of the decorated state to next in line.
	template <typename... Args>
	CanAttack(Args... args) : T(std::forward<Args>(args)...) {}
};