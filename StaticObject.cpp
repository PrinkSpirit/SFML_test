#include <cstdlib>
#include <iostream>

#include "StaticObject.h"

unsigned int StaticObject::counter = 0;


StaticObject::StaticObject(glm::vec2 pos, const sf::Texture *texture, float isSolid) : 
	GameObject(pos, texture), isSolid(isSolid), id(counter++)
{
}

StaticObject::~StaticObject()
{

}

BlockFactory* BlockFactory::instance = nullptr;

BlockFactory::BlockFactory()
{
	display = Display::Instance();
}

void BlockFactory::loadTextures(BlockType type)
{
	sf::Texture* texture = new sf::Texture();
	try {
		switch (type) {
		case BlockType::Brick:
			texture->loadFromFile("./sprites/brick.png");
			break;
		default:
			break;
		}

	}
	catch(std::exception&) {
		std::cerr << "Could not load texture" << std::endl;
		terminate();
	}
	
	textureMap[type] = texture;
}

BlockFactory::~BlockFactory()
{
	objectList.clear();
}

BlockFactory* BlockFactory::Instance()
{
	if (instance == nullptr) {
		int attempts = 0;
		do {
			instance = new BlockFactory();
			attempts++;
		} while (instance==nullptr && attempts < 5);
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

StaticObject* BlockFactory::createStaticObject(BlockType type, glm::vec2 pos)
{
	std::shared_ptr<StaticObject> block = nullptr;
	switch (type) {
		case BlockType::Brick:
			if (textureMap.find(type) == textureMap.end())
				loadTextures(type);
			block = std::shared_ptr<StaticObject>(new StaticObject(pos, textureMap[BlockType::Brick], true));
			break;
		
		default:
			break;
	}

	objectList.push_back(block);
	display->addSprite(block.get());
	return block.get();
}
