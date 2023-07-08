#pragma once

#include "ObjectFactory.h"
#include "StaticObject.h"


/// <summary>
/// Creates static objects elements and keep a pointer on them.
/// Singleton. Factory. Inherits from ObjectFactory.
/// </summary>
class BlockFactory : public ObjectFactory
{
protected:
	BlockFactory();
	static BlockFactory* instance;

public:
	~BlockFactory();

	/// <summary>
	/// Returns the instance of the BlockFactory.
	/// If the instance doesn't exist, creates it.
	/// </summary>
	/// <returns>BlockFactory singleton pointer</returns>
	static BlockFactory* Instance();

	/// <summary>
	/// Deletes the instance of the BlockFactory.
	/// Is set to be called at automaticaly at the end of the program.
	/// </summary>
	static void release();

	/// <summary>
	/// Main method of the factory. Creates a static object of the given type at the given position.
	/// </summary>
	/// <param name="type">Type of the created object</param>
	/// <param name="pos">Position of the created object</param>
	/// <returns></returns>
	virtual GameObject* createObject(ObjectType type, glm::vec2 pos) override;
};

