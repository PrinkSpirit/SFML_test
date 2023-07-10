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
				texture->loadFromFile("./sprites/Blocks.png");
			break;
		case ObjectType::Link:
				texture->loadFromFile("./sprites/Link.png");
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
	case ObjectType::Block:
	case ObjectType::Dirt:
	case ObjectType::Cloud1:
	case ObjectType::Cloud2:
	case ObjectType::Cloud3:
	case ObjectType::pillarHead:
	case ObjectType::pillar:
	case ObjectType::armorTop:
	case ObjectType::armorBottom:
		// If texture is not in our map we load it
		if (m_textureMap.find(ObjectType::Brick) == m_textureMap.end())
			loadTexture(ObjectType::Brick);
		return m_textureMap[ObjectType::Brick];
	default:
		break;
	}
	return nullptr;
}

ObjectFactory::~ObjectFactory()
{
	for (auto object : m_objectList) {
		delete object;
	}
	m_objectList.clear();
}
