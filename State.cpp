#include "State.h"


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

PlayerState::PlayerState(Actor* actor)
{
}

PlayerState::~PlayerState()
{
}
