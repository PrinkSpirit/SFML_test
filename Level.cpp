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
		// Call all actors' update function
		actor->update(dT);

		// Check for collisions
		for (auto object : m_StaticObjectList) {
			if (intersects(actor->getPosition(), actor->getPosition() + actor->getSize(), object->getPosition(), object->getPosition() + object->getSize())) {
				handleCollision(actor, object, dT);
			}
		}

		boundingBoxCollision(actor, dT);
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

bool intersects(glm::vec2 A1, glm::vec2 A2, glm::vec2 B1, glm::vec2 B2)
{
	return (A1.x < B2.x && A2.x > B1.x && A1.y < B2.y && A2.y > B1.y);
}

void handleCollision(Actor* actor, GameObject* object, float dT)
{
	glm::vec2 Ap = actor->getPosition();
	glm::vec2 As = actor->getSize();

	glm::vec2 Bp = actor->getPosition();
	glm::vec2 Bs = actor->getSize();

	if (actor->getVelocity().y < 0) { // Falling
		actor->setPosition(glm::vec2(Ap.x, Bp.y));
		actor->setVelocity(glm::vec2(actor->getVelocity().x, 0.0f));
	}

	if (actor->getVelocity().y > 0.01) {
		actor->setPosition(glm::vec2(Ap.x, Bp.y - As.y));
		actor->setVelocity(glm::vec2(actor->getVelocity().x, 0.0f));
	}

	if (intersects(actor->getPosition(), actor->getPosition() + actor->getSize(), object->getPosition(), object->getPosition() + object->getSize())) {
		if (actor->getVelocity().x > 0) {
			actor->setPosition(glm::vec2(Bp.x - Bs.x / 2.0f, Ap.y));
			actor->setVelocity(glm::vec2(0.0f, actor->getVelocity().y));
		}
		
		if (actor->getVelocity().x < 0) {
			actor->setPosition(glm::vec2(Bp.x + Bs.x / 2.0f, Ap.y));
			actor->setVelocity(glm::vec2(0.0f, actor->getVelocity().y));
		}
	}

	//float Ah = A->element->sprite->w;
	//float Aw = A->element->sprite->h;

	//float Bx = B->pos_x;
	//float By = B->pos_y;
	//float Bh = B->sprite->w;
	//float Bw = B->sprite->h;

	//if (A->v_a > 0) { // Is falling
	//	A->element->pos_y = By - Bh - Ah;
	//	A->v_a = 0;
	//}

	//if (A->v_a < 0) { // Is rising
	//	A->element->pos_y = By;
	//	A->v_a = 0;
	//}
	//A->element->sprite->x = (int)A->element->pos_x;
	//A->element->sprite->y = (int)A->element->pos_y;

	//if (isColliding(A->element, B)) {
	//	if (A->h_a > 0) { // Is going right
	//		A->element->pos_x = Bx - Aw; // New position is B minus A's Sprite width
	//		A->h_a = 0; // Momentum is cut
	//	}

	//	if (A->h_a < 0) { // Is going left
	//		A->element->pos_x = Bx + Bw; // New position is B plus B's Sprite width
	//		A->h_a = 0; // Momentum is cut
	//	}

	//	A->element->sprite->x = (int)A->element->pos_x;
	//	A->element->sprite->y = (int)A->element->pos_y;
	//}
}
