#pragma once

class Actor;

class ActorState
{
protected:
	Actor* m_actor;

public:
	virtual void in() = 0;
	virtual void update() = 0;
	virtual void out() = 0;

	ActorState() = delete;
	ActorState(Actor* actor);
	virtual ~ActorState();
};

