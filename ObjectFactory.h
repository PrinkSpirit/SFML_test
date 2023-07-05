#pragma once

#include <vector>
#include <glm.hpp>
#include <map>

#include "Display.h"
#include "GameObject.h"


enum class ObjectType {
	Link,
	Brick,
};

class ObjectFactory
{
protected:
	ObjectFactory();
	Display* display = nullptr;

	std::vector<GameObject*> m_objectList;
	std::map<ObjectType, sf::Texture*> m_textureMap;

	void loadTexture(ObjectType type);
public:
	virtual ~ObjectFactory();

	virtual GameObject* createObject(ObjectType type, glm::vec2 pos) = 0;
};

