#pragma once
#include "Pawn.h"
#include "Controller.h"
#include "State.h"

class Player : public Pawn
{
protected:
	bool m_jumping = false; /// Whether the player is jumping.
	bool m_grounded = false; /// Whether the player is on the ground.

	Controller* m_controller = nullptr;			/// Pointer to the control manager

	class PlayerState;
	class Idle;
	class Walk;
	class Jump;
	class Crouch;
	class Attack;

	template <class T>
	class CanFall;
	template <class T>
	class CanMove;
	template <class T>
	class CanJump;
	template <class T>
	class CanWalk;


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


/* ---------- States ---------- */
/// @brief State base class for players.
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
	float m_idleTimer = 0.0f;


public:
	void in(float dT);
	void out(float dT);
	void update(float dT);

	Walk(Player*);
	~Walk();
};

/// @brief Jumping.
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

class Player::Crouch;
class Player::Attack;


/* ---------- Decorators ---------- */

/* ---------- State Action ---------- */
;
/// @brief Handle horizontal movement for the current state.
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


	template <typename... Args>
	CanMove(Args... args) : T(std::forward<Args>(args)...) {}

	~CanMove() {}
};

/// @brief Handle gravity for the current state. Indicate that the player can fall.
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


	template <typename... Args>
	CanFall(Args... args) : T(std::forward<Args>(args)...) {}

	~CanFall() {}
};

/* -------- State Switchers ---------- */

/// @brief Handle the jumping action in the decorated state.
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


	template <typename... Args>
	CanJump(Args... args) : T(std::forward<Args>(args)...) {}

	~CanJump() {}
};



/// @brief Check for left and right actions while grounded.
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


	template <typename... Args>
	CanWalk(Args... args) : T(std::forward<Args>(args)...) {}
};

// can crouch
// can attack