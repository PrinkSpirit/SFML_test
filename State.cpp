#include "State.h"


ActorState::ActorState(Actor* actor) : m_actor(actor)
{
}

ActorState::~ActorState()
{
	m_actor = nullptr;
}
