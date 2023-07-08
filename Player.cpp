#include "Player.h"

Player::Player() : Pawn()
{
}

Player::Player(glm::vec2 pos, const sf::Texture& texture) : Pawn(pos, texture)
{
	m_speed = glm::vec2(100.0f,200.0f); // Speed, magic number.

    // Reference to the iddle position on the sprite sheet
    this->sprite->setTextureRect(sf::IntRect(0, 0, 32, 32)); 
    this->size = { sprite->getTextureRect().width / 1.5, sprite->getTextureRect().height};
    this->sprite->setOrigin(size.x/2.0f, size.y/2.0f);

    m_animations.push_back(sf::IntRect(0, 0, 32, 32));  // Iddle / Walk 1
    m_animations.push_back(sf::IntRect(64, 0, 32, 32)); // Walk 2
    m_animations.push_back(sf::IntRect(96, 0, 32, 32)); // Walk 3
    m_animations.push_back(sf::IntRect(32, 0, 32, 32)); // Walk 4
    m_animations.push_back(sf::IntRect(64, 0, 32, 32)); // Walk 5
    m_animations.push_back(sf::IntRect(96, 0, 32, 32)); // Walk 6 / jumping
}

Player::Player(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture) : Pawn(pos, size, texture)
{
}

Player::~Player()
{
}

bool Player::isJumping() const
{
	return m_jumping;
}

void Player::jump()
{
    if (!m_jumping) {
        this->state = State::jumping;
		m_jumping = true;
		velocity.y = m_speed.y / 7500.0f;
	}
}

//void Player::move(int input)
//{
//
//}

void Player::update(float dT)
{
	if (m_controller != nullptr) {
        
        //this->state = State::iddle;
        if (m_controller->up()) {
            //move(glm::vec2(0, 1));
            this->velocity.y += this->m_speed.y * dT;
        }
        if (m_controller->down()) {
            //move(glm::vec2(0, -1));
            this->velocity.y -= this->m_speed.y * dT;
        }
        if (m_controller->left()) {
            //move(glm::vec2(-1, 0));
            this->velocity.x -= this->m_speed.x * dT;
            if (this->state == State::movingLeft) {
                this->animTimer += dT;
            } else {
				this->animTimer = 0.0f;
				this->state = State::movingLeft;
			}
        }
        if (m_controller->right()) {
            //move(glm::vec2(1, 0));
            this->velocity.x += this->m_speed.x * dT;
            if (this->state == State::movingRight) {
                this->animTimer += dT;
            }
            else {
                this->animTimer = 0.0f;
                this->state = State::movingRight;
            }
        }

        if (m_controller->jump()) {
            jump();
        }

        if (this->state == State::movingLeft || this->state == State::movingRight) {
            this->sprite->setTextureRect(m_animations[((int)(this->animTimer * 12) % 6)]);
        }
        else if (this->state == State::jumping) {
			this->sprite->setTextureRect(sf::IntRect(3 * 32, 0, 32, 32));
		}
		else {
			this->sprite->setTextureRect(sf::IntRect(0, 0, 32, 32));
		}
	}
    sf::Vector2f s = sprite->getScale();

    if ((velocity.x < 0 && s.x > 0) || (velocity.x > 0 && s.x < 0)) {
        this->sprite->setScale(-s.x, s.y);
    }

    // Call the parent update function
	Pawn::update(dT);

    // Check if the player is on the ground after the position update
    if (this->velocity.y >= -0.01f && this->velocity.y <= 0.01f && m_controller != nullptr) {
        if (!m_controller->jump()) {
			m_jumping = false;
		}
	}
}

void Player::setController(Controller* controller)
{
    this->m_controller = controller;
}

Controller* Player::getController() const
{
    return this->m_controller;
}
