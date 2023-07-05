#include "ActorFactory.h"


ActorFactory* ActorFactory::instance = nullptr;

ActorFactory::ActorFactory()
{
}

ActorFactory::~ActorFactory()
{
}

ActorFactory* ActorFactory::Instance()
{
	if (instance == nullptr) {
		int attempts = 0;
		do {
			instance = new ActorFactory();
			attempts++;
		} while (instance == nullptr && attempts < 5);
		if (instance == nullptr) {
			std::cerr << "Could not create ActorFactory" << std::endl;
			terminate();
		}
		std::atexit(release);
	}

	return instance;
}

void ActorFactory::release()
{
	delete instance;
}

GameObject* ActorFactory::createObject(ObjectType type, glm::vec2 pos)
{
	GameObject* actor = nullptr;
	switch (type) {
	case ObjectType::Link:
		if (m_textureMap.find(type) == m_textureMap.end())
			loadTexture(type);
		actor = (Actor*)new Player(pos, *m_textureMap[ObjectType::Link]);
		break;

	default:
		break;
	}

	m_objectList.push_back(actor);
	display->addSprite(actor);
	return actor;
}

Player* ActorFactory::createPlayer(ObjectType type, glm::vec2 pos)
{
	Player* player = nullptr;
	switch (type) {
	case ObjectType::Link:
		if (m_textureMap.find(type) == m_textureMap.end())
			loadTexture(type);
		player = new Player(pos, *m_textureMap[ObjectType::Link]);
		break;

	default:
		break;
	}

	m_objectList.push_back(player);
	display->addSprite(player);
	return player;
}

