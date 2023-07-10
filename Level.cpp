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
		m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Dirt, glm::vec2(i * 16, 0 * 16)));
	}

	for (int i = 0; i < 22; i++) {
		m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Dirt, glm::vec2(i * 16, 1 * 16)));
	}

	for (int i = 6; i < 22; i++) {
		m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Brick, glm::vec2(i * 16, 2 * 16)));
	}

	for (int i = 8; i < 22; i++) {
		m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Brick, glm::vec2(i * 16, 3*16)));
	}

	for (int i = 10; i < 12; i++) {
		m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Block, glm::vec2(i * 16, 4*16)));
	}

	for (int i = 10; i < 16; i++) {
		m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Brick, glm::vec2(i * 16, 12 * 16)));
	}

	for (int i = 11; i < 16; i++) {
		m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Brick, glm::vec2(i * 16, 11 * 16)));
	}


	m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Cloud1, glm::vec2(4 * 16 , 9 * 16)));
	m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Cloud3, glm::vec2(5 * 16, 9 * 16)));

	m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Cloud1, glm::vec2(6 * 16, 7 * 16)));
	m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::Cloud2, glm::vec2(7 * 16, 7 * 16)));

	m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::armorTop, glm::vec2(10 * 16, 6 * 16)));
	m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::armorBottom, glm::vec2(10 * 16, 5 * 16)));

	for (int i = 4; i < 10; i++)
		m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::pillar, glm::vec2(14 * 16, i * 16)));
	m_StaticObjectList.push_back(BlockFactory::Instance()->createObject(ObjectType::pillarHead , glm::vec2(14 * 16, 10 * 16)));

	display->setBackgroundColor(sf::Color(92, 148, 252, 255));


	this->player = (Player*)ActorFactory::Instance()->createPlayer(ObjectType::Link, glm::vec2(4 * 16, 4 * 16));
	m_ActorList.push_back(player);
}


void Level::update(float dT)
{
	for (auto actor : m_ActorList) {
		// Call all actors' update function
		actor->update(dT);

		// Check for collisions
		for (auto object : m_StaticObjectList) {
			/*if (intersects(actor->getPosition(), actor->getPosition() + actor->getSize(), object->getPosition(), object->getPosition() + object->getSize())) {
				handleCollision(actor, object, dT);
			}*/
			handleCollision(actor, object, dT);
		}

		boundingBoxCollision(actor, dT);
		actor->setVelocity(glm::vec2(0.0f, actor->getVelocity().y));
	}
}

void Level::boundingBoxCollision(Actor* actor, float dT)
{
	// Should velocity be just attenuated instead ?
	if (actor->getPosition().x <= this->origin.x) {
		actor->setPosition(glm::vec2(this->origin.x, actor->getPosition().y));
		actor->setVelocity(glm::vec2(0.0f, actor->getVelocity().y));
	}

	if (actor->getPosition().x > this->origin.x + this->size.x - actor->getSize().x) {
		actor->setPosition(glm::vec2(this->origin.x + this->size.x - actor->getSize().x, actor->getPosition().y));
		actor->setVelocity(glm::vec2(0.0f, actor->getVelocity().y));
	}

	if (actor->getPosition().y <= 0) {
		actor->setPosition(glm::vec2(actor->getPosition().x, 0));
		actor->setVelocity(glm::vec2(actor->getVelocity().x, 0.0f));
	}

	if (actor->getPosition().y > this->origin.y + this->size.y - actor->getSize().y) {
		actor->setPosition(glm::vec2(actor->getPosition().x, this->origin.y + this->size.y - actor->getSize().y));
		actor->setVelocity(glm::vec2(actor->getVelocity().x, 0.0f));
	}
}

bool intersects(glm::vec2 A1, glm::vec2 A2, glm::vec2 B1, glm::vec2 B2) {
	return (A1.x < B2.x + epsilon && A2.x > B1.x - epsilon && A1.y < B2.y + epsilon && A2.y > B1.y - epsilon);
}

void handleCollision(Actor* actor, GameObject* object, float dT)
{
	// if actor horizontal velocity > 0
	//  - Handle collision with left side of object
	//  - Hitbox with minus epsillon on the right 

	// Horizontal and vertical epsilon
	glm::vec2 Eh = glm::vec2(2.0f, 0.0f);
	glm::vec2 Ev = glm::vec2(0.0f, 2.0f);

	glm::vec2 Ap = actor->getPosition();
	glm::vec2 As = actor->getSize();
	glm::vec2 Av = actor->getVelocity();

	glm::vec2 Bp = object->getPosition();
	glm::vec2 Bs = object->getSize();

	if (Av.y < 0 && intersects(Ap, Ap + As, Bp + Ev + Eh, Bp + Bs - Eh)) { // Falling
		Ap.y = Bp.y + Bs.y;
		Av.y = 0.0f;
	}

	if (Av.y > 0 && intersects(Ap, Ap + As, Bp + Eh, Bp + Bs - Ev - Eh)) { // Rising
		Ap.y = Bp.y - As.y;
		Av.y = 0.0f;
	}

	if (Av.x < 0 && intersects(Ap, Ap + As, Bp + Ev, Bp + Bs - Ev)) { // Moving left
		Ap.x = Bp.x + Bs.x;
		Av.x = 0.0f;
	}

	if (Av.x > 0 && intersects(Ap, Ap + As, Bp + Ev , Bp + Bs - Ev)) { // Moving right
		Ap.x = Bp.x - As.x;
		Av.x = 0.0f;
	}

	actor->setPosition(Ap);
	actor->setVelocity(Av);
}
