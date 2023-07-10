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
		block = new StaticObject(pos, glm::vec2(16.0f,16.0f), *getTexture(type), true);
		block->getSprite()->setTextureRect(sf::IntRect(0, 0, 16, 16));
		break;
	case ObjectType::Block:
		block = new StaticObject(pos, glm::vec2(16.0f, 16.0f), *getTexture(type), true);
		block->getSprite()->setTextureRect(sf::IntRect(16, 0, 16, 16));
		break;
	case ObjectType::Dirt:
		block = new StaticObject(pos, glm::vec2(16.0f, 16.0f), *getTexture(type), true);
		block->getSprite()->setTextureRect(sf::IntRect(2 * 16, 0, 16, 16));
		break;
	case ObjectType::Cloud1:
		block = new StaticObject(pos, glm::vec2(16.0f, 16.0f), *getTexture(type), false);
		block->getSprite()->setTextureRect(sf::IntRect(0, 16, 16, 16));
		break;
	case ObjectType::Cloud2:
		block = new StaticObject(pos, glm::vec2(16.0f, 16.0f), *getTexture(type), false);
		block->getSprite()->setTextureRect(sf::IntRect(16, 16, 16, 16));
		break;
	case ObjectType::Cloud3:
		block = new StaticObject(pos, glm::vec2(16.0f, 16.0f), *getTexture(type), false);
		block->getSprite()->setTextureRect(sf::IntRect(2 * 16, 16, 16, 16));
		break;
	case ObjectType::pillarHead:
		block = new StaticObject(pos, glm::vec2(16.0f, 16.0f), *getTexture(type), false);
		block->getSprite()->setTextureRect(sf::IntRect(3 * 16, 0, 16, 16));
		break;
	case ObjectType::pillar:
		block = new StaticObject(pos, glm::vec2(16.0f, 16.0f), *getTexture(type), false);
		block->getSprite()->setTextureRect(sf::IntRect(4 * 16, 0, 16, 16));
		break;
	case ObjectType::armorTop:
		block = new StaticObject(pos, glm::vec2(16.0f, 16.0f), *getTexture(type), false);
		block->getSprite()->setTextureRect(sf::IntRect(5 * 16, 0, 16, 16));
		break;
	case ObjectType::armorBottom:
		block = new StaticObject(pos, glm::vec2(16.0f, 16.0f), *getTexture(type), false);
		block->getSprite()->setTextureRect(sf::IntRect(6 * 16, 0, 16, 16));
		break;
	default:
		break;
	}

	m_objectList.push_back(block);
	display->addSprite(block);
	return block;
}