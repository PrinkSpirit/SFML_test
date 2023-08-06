#pragma once

/// @brief State base class. Pure virtual.
class State
{
public:
	/// @brief Function called when the state is entered.
	/// @param dT Delta time.
	virtual void in(float) = 0;
	/// @brief Function called at state exit.
	/// @param dT Delta time.
	virtual void out(float) = 0;

	/// @brief Function called every tick.
	/// @param dt Delta time.
	virtual void update(float) = 0;

	/// @brief Contructor deleted since this is a pure virtual class.
	State();

	/// @brief Empty destructor.
	virtual ~State();
};


class Actor; // Forward declaration

/// @brief State base class for actors.
class ActorState : public State
{
protected:
	/// @brief Pointer to the actor.
	Actor* m_actor;

public:
	ActorState() = delete;
	/// @brief Contructor, requires a pointer to the actor.
	/// @param actor Pointer to the actor.
	ActorState(Actor*);
	virtual ~ActorState();
};

//class Player; // Forward declaration


