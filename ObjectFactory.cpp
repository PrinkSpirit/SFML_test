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

ObjectFactory::~ObjectFactory()
{
	for (auto object : m_objectList) {
		delete object;
	}
	m_objectList.clear();
}
