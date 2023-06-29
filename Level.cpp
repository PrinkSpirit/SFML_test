#include "Level.h"

Level::Level()
{
	display = Display::Instance();

	ObjectList = new std::vector<StaticObject*>();
	ActorList = new std::vector<Actor*>();
	player = nullptr;

}

Level::~Level()
{
	delete ObjectList;
	delete ActorList;
}

void Level::addStaticObject(StaticObject* object)
{
	ObjectList->push_back(object);
}

void Level::addActor(Actor* actor)
{
	ActorList->push_back(actor);
}

void Level::setPlayer(Player* player)
{
	this->player = player;
}

