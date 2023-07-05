#include "BlockFactory.h"


BlockFactory* BlockFactory::instance = nullptr;

BlockFactory::BlockFactory()
{
}

BlockFactory::~BlockFactory()
{
}

BlockFactory* BlockFactory::Instance()
{
	if (instance == nullptr) {
		int attempts = 0;
		do {
			instance = new BlockFactory();
			attempts++;
		} while (instance == nullptr && attempts < 5);
		if (instance == nullptr) {
			std::cerr << "Could not create BlockFactory" << std::endl;
			terminate();
		}
		std::atexit(release);
	}

	return instance;
}

void BlockFactory::release()
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

GameObject* BlockFactory::createObject(ObjectType type, glm::vec2 pos)
{
	GameObject* block = nullptr;
	switch (type) {
	case ObjectType::Brick:
		if (m_textureMap.find(type) == m_textureMap.end())
			loadTexture(type);
		block = new StaticObject(pos, *m_textureMap[ObjectType::Brick], true);
		break;

	default:
		break;
	}

	m_objectList.push_back(block);
	display->addSprite(block);
	return block;
}