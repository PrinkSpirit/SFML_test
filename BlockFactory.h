#pragma once

#include "ObjectFactory.h"
#include "StaticObject.h"

class BlockFactory : public ObjectFactory
{
protected:
	BlockFactory();
	static BlockFactory* instance;

public:
	~BlockFactory();
	static BlockFactory* Instance();
	static void release();

	virtual GameObject* createObject(ObjectType type, glm::vec2 pos) override;
};

