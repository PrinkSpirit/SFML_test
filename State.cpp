#include "State.h"


State::State()
{
}

State::~State()
{
}

ActorState::ActorState(Actor* actor) : m_actor(actor)
{
}

ActorState::~ActorState()
{
	m_actor = nullptr;
}

