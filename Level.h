#pragma once

#include <vector>

#include "StaticObject.h"
#include "Player.h"
#include "Display.h"

class Level
{
protected:
	std::vector<StaticObject*>* ObjectList; // List all the static objects in the Level
	std::vector<Actor*>* ActorList; // List all the actors in the Level
	
	Player* player = nullptr;
	Display* display = nullptr;

public:
	Level();
	~Level();

	void addStaticObject(StaticObject* object);
	void addActor(Actor* actor);
	void setPlayer(Player* player);
};

