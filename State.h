#pragma once

class State
{
public:
	virtual void in(float dT) = 0;
	virtual void update(float dT) = 0;
	virtual void out(float dT) = 0;

	State();
	virtual ~State();
};

class Actor;
class ActorState : public State
{
protected:
	Actor* m_actor;

public:
	ActorState() = delete;
	ActorState(Actor* actor);
	virtual ~ActorState();
};

class Player;

class PlayerState : public State {
protected:
	Player* m_player;

public:
	PlayerState() = delete;
	PlayerState(Actor* actor);
	virtual ~PlayerState();
};