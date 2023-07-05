#pragma once

#include <vector>
#include <map>
#include <string>

#include "ObjectFactory.h"
#include "Player.h"
#include "Display.h"


class ActorFactory : public ObjectFactory
{
protected:
	ActorFactory();
	static ActorFactory* instance;

public:
	~ActorFactory();
	static ActorFactory* Instance();
	static void release();

	GameObject* createObject(ObjectType type, glm::vec2 pos);
	Player* createPlayer(ObjectType type, glm::vec2 pos);
};
