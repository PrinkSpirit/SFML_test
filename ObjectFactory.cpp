#include "ObjectFactory.h"

ObjectFactory::ObjectFactory()
{
	this->display = Display::Instance();
}

void ObjectFactory::loadTexture(ObjectType type)
{
	sf::Texture* texture = new sf::Texture();
	try {
		switch (type) {
		case ObjectType::Brick:			
				texture->loadFromFile("./sprites/brick.png");
			break;
		case ObjectType::Link:
				texture->loadFromFile("./sprites/Link.bmp");
			break;
		default:
			break;
		}

	}
	catch (std::exception&) {
		std::cerr << "Could not load texture" << std::endl;
		//terminate();
	}

	m_textureMap[type] = texture;
}

sf::Texture* ObjectFactory::getTexture(ObjectType type)
{
	// Translate the type for objects sharing a sprite sheet
	switch (type)
	{	
	case ObjectType::Link:
		if (m_textureMap.find(ObjectType::Link) == m_textureMap.end())
			loadTexture(ObjectType::Link);
		return m_textureMap[ObjectType::Link];
	case ObjectType::Brick:
		if (m_textureMap.find(ObjectType::Brick) == m_textureMap.end())
			loadTexture(ObjectType::Brick);
		return m_textureMap[ObjectType::Brick];
	default:
		break;
	}

	
		loadTexture(type);
	
}

ObjectFactory::~ObjectFactory()
{
	for (auto object : m_objectList) {
		delete object;
	}
	m_objectList.clear();
}
