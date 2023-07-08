#pragma once

#include <vector>

#include "StaticObject.h"
#include "ActorFactory.h"
#include "BlockFactory.h"
#include "Player.h"
#include "Display.h"


/// <summary>
/// This class represents a level in the game. It contains and manage all 
/// the static objects and actors in the level.
/// </summary>
class Level
{
protected:
	std::vector<GameObject*> m_StaticObjectList; // List all the static objects in the Level
	std::vector<Actor*> m_ActorList; // List all the actors in the Level
	
	/// Origin point of the level. This is the bottom left corner of the level.
	glm::vec2 origin{0,0};
	/// Size of the level in arbitrary unit.
	glm::vec2 size{256,240};

	/// Pointer to the player object
	Player* player = nullptr;
	/// Pointer to the display manager
	Display* display = nullptr;

public:
	Level();
	~Level();

	/// <summary>
	/// Add a static element to the level.
	/// </summary>
	/// <param name="object">Pointer to a static object</param>
	void addStaticObject(StaticObject* object);

	/// <summary>
	/// Add and actor to the level.
	/// </summary>
	/// <param name="actor">Pointer to an actor</param>
	void addActor(Actor* actor);

	/// <summary>
	/// Set the pointer to the player object.
	/// </summary>
	/// <param name="player">Pointer to the player</param>
	void setPlayer(Player* player);

	/// <summary>
	/// Returns the player object.
	/// </summary>
	/// <returns>Pointer to the player</returns>
	Player* getPlayer();

	/// <summary>
	/// Placeholder. Creates a test level.
	/// </summary>
	void testLevel();

	/// <summary>
	/// Updates all actors in the level.
	/// </summary>
	/// <param name="dT">Delta Time - Time elapsed since last function call</param>
	void update(float dT);

	/// <summary>
	/// Check collisions with the level's boundaries
	/// </summary>
	/// <param name="actor">Actor checked</param>
	/// <param name="dT">Delta time</param>
	void boundingBoxCollision(Actor* actor, float dT);
};

