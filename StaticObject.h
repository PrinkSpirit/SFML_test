#pragma once

#include <vector>
#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Display.h"
#include "GameObject.h"


enum class BlockType {
	Brick,
};

class StaticObject : public GameObject
{
protected:
	static unsigned int counter;
	int id;
	bool isSolid = true;

public:
	StaticObject() = delete;
	StaticObject(glm::vec2 pos, const sf::Texture &texture, float isSolid);
	virtual ~StaticObject();
};

class BlockFactory
{
protected:
	BlockFactory();
	static BlockFactory* instance;
	Display* display = nullptr;

	std::vector<std::shared_ptr<StaticObject>> objectList;
	std::map<BlockType, sf::Texture*> textureMap;

	void loadTextures(BlockType type);

public:
	~BlockFactory();
	static BlockFactory* Instance();
	static void release();

	StaticObject* createStaticObject(BlockType type, glm::vec2 pos);
};