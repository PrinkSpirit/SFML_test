#include "Level.h"

Level::Level()
{
	display = Display::Instance();
	player = nullptr;

}

Level::~Level()
{
}

void Level::addStaticObject(StaticObject* object)
{
	m_StaticObjectList.push_back(object);
}

void Level::addActor(Actor* actor)
{
	m_ActorList.push_back(actor);
}

void Level::setPlayer(Player* player)
{
	this->player = player;
}

Player* Level::getPlayer()
{
	return this->player;
}

void Level::testLevel()
{
	for (int i = 0; i < 22; i++) {

		m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Brick, glm::vec2(i * 16, 0)));
	}

	m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Brick, glm::vec2(0, 4 * 16)));

	display->setBackgroundColor(sf::Color(92, 148, 252, 255));


	this->player = (Player*)ActorFactory::Instance()->createPlayer(ObjectType::Link, glm::vec2(4 * 16, 4 * 16));
	m_ActorList.push_back(player);
}

void Level::update(float dT)
{
	for (auto actor : m_ActorList) {
		actor->update(dT);


		if(actor->getPosition().x <= this->origin.x)
		{
			actor->setPosition(glm::vec2(this->origin.x, actor->getPosition().y));
			actor->setVelocity(glm::vec2(0.0f, actor->getVelocity().y));
		}

		if (actor->getPosition().x > this->origin.x + this->size.x - actor->getSize().x)
		{
			actor->setPosition(glm::vec2(this->origin.x + this->size.x - actor->getSize().x, actor->getPosition().y));
			actor->setVelocity(glm::vec2(0.0f, actor->getVelocity().y));
		}

		if (actor->getPosition().y <= 0)
		{
			actor->setPosition(glm::vec2(actor->getPosition().x, 0));
			actor->setVelocity(glm::vec2(actor->getVelocity().x, 0.0f));
		}

		if(actor->getPosition().y > this->origin.y + this->size.y - actor->getSize().y)
		{
			actor->setPosition(glm::vec2(actor->getPosition().x, this->origin.y + this->size.y - actor->getSize().y));
			actor->setVelocity(glm::vec2(actor->getVelocity().x, 0.0f));
		}
	}
}

