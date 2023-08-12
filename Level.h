#pragma once

#include <vector>

#include "StaticObject.h"
#include "ActorFactory.h"
#include "BlockFactory.h"
#include "Player.h"
#include "Display.h"


const float epsilon = 0.00001f;

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

	/// @brief Add a static element to the level.
	/// @param object Pointer to a static object.
	void addStaticObject(StaticObject* object);

	/// <summary>
	/// Add and actor to the level.
	/// </summary>
	/// <param name="actor">Pointer to an actor</param>
	void addActor(Actor* actor);

	/// @brief Set the pointer to the player object.
	/// @param player Pointer to the player.
	void setPlayer(Player* player);

	/// @brief Returns the player object.
	/// @return Pointer to the player.
	Player* getPlayer();

	/// @brief Placeholder. Creates a test level.
	void testLevel();

	/// @brief Updates all actors in the level.
	/// @param dT Delta Time - Time elapsed since last function call
	void update(float dT);

	

	/// @brief Check collisions with the level's boundaries
	/// @param actor Actor checked.
	/// @param dT Delta time.
	void boundingBoxCollision(Actor* actor, float dT);
};

/// @brief Check if two rectangles overlap.
/// @param A1 Bottom left corner of the first rectangle.
/// @param A2 Top right corner of the first rectangle.
/// @param B1 Bottom left corner of the second rectangle.
/// @param B2 Top right corner of the second rectangle.
/// @returns Boolean.
bool intersects(glm::vec2 A1, glm::vec2 A2, glm::vec2 B1, glm::vec2 B2);

void handleCollision(Actor* actor, GameObject* object, float dT);