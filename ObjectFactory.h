#pragma once

#include <vector>
#include <glm.hpp>
#include <map>

#include "Display.h"
#include "GameObject.h"

/// <summary>
/// List of all the type of object in the game.
/// </summary>
enum class ObjectType {
	Link,	// The player in side-scrolling sections
	Brick,	// Simple wall element.
	Block,
	Dirt,	// Simple ground element.
	Cloud1,
	Cloud2,
	Cloud3,
	pillarHead,
	pillar,
	armorTop,
	armorBottom,
};

/// <summary>
/// Virtual class that represent a factory of game object.
/// </summary>
class ObjectFactory
{
protected:
	ObjectFactory();
	/// Pointer to the display manager singleton
	Display* display = nullptr;

	/// Pointer to all the object created by the factory
	std::vector<GameObject*> m_objectList;
	/// Map of all the texture used by the factory to create objects
	std::map<ObjectType, sf::Texture*> m_textureMap;

	/// <summary>
	/// Load the texture for a givent object type.
	/// </summary>
	/// <param name="type">Object type</param>
	void loadTexture(ObjectType type);
	
	/// <summary>
	/// Check if the texture for a given object type is already loaded.
	/// If not, load it.
	/// Return a pointer to the texture.
	/// </summary>
	/// <param name="type">Object type</param>
	/// <returns>Pointer to the texture</returns>
	sf::Texture* getTexture(ObjectType type);
public:
	virtual ~ObjectFactory();

	/// <summary>
	/// Create a specified object at the given position.
	/// Virtual method, must be implemented by the child class.
	/// </summary>
	/// <param name="type">Type of the object</param>
	/// <param name="pos">Position where to spawn the object in</param>
	/// <returns>Pointer to the created object</returns>
	virtual GameObject* createObject(ObjectType type, glm::vec2 pos) = 0;
};

