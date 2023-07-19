#pragma once

#include "Actor.h"

class State
{
protected:
	Actor* m_actor;

public:
	void stateEntry();
	void stateUpdate();
	void stateExit();

	State() = delete;
	State(Actor* actor);
	virtual ~State();
};

