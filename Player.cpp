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

void Player::jump(float dT)
{
    if (m_state!=PlayerState::jumping) {
        this->m_state = PlayerState::jumping;
		m_jumping = true;
		velocity.y = m_speed.y / 7500.0f;
        this->sprite->setTextureRect(sf::IntRect(3 * 32, 0, 32, 32));
	}
    if (m_state == PlayerState::jumping) {
        if (m_controller->left()) {  // Lateral air control
            this->velocity.x -= this->m_speed.x * dT;
        }
		else if (m_controller->right()) {
			this->velocity.x += this->m_speed.x * dT;
		}
    }
    if (velocity.y < 0 - FLT_EPSILON) {
        m_state = PlayerState::falling;
    }
}

void Player::fall(float dT)
{
    this->sprite->setTextureRect(sf::IntRect(3 * 32, 0, 32, 32));
    if (m_controller->left()) {  // Lateral air control
        this->velocity.x -= this->m_speed.x * dT;
    }
    else if (m_controller->right()) {
        this->velocity.x += this->m_speed.x * dT;
    }
    if (velocity.y > -FLT_EPSILON) {
        m_state = PlayerState::idle;
    }
}

void Player::idle(float dT)
{
    if (m_controller->left() || m_controller->right()) {
        move(dT);
	} else if (m_controller->jump()) {
        jump(dT);
	}
    if (velocity.y < -FLT_EPSILON) {
        m_state = PlayerState::falling;
    }
}

void Player::move(float dT)
{    
    if (m_controller->left() && m_state == PlayerState::movingLeft) {  // If the player is still moving in the same direction
        this->velocity.x -= this->m_speed.x * dT;
        this->m_animTimer += dT;    // We increment the animation timer
    } 
    else if (m_controller->left()) { // else
        this->velocity.x -= this->m_speed.x * dT;
        this->m_animTimer = 0.0f;   // We reset the animation timer
        m_state = PlayerState::movingLeft; // And set the state to moving left
    }

    if (m_controller->right() && m_state == PlayerState::movingRight) {
        this->velocity.x += this->m_speed.x * dT;
        this->m_animTimer += dT;
    } 
    else if (m_controller->right() ) {  
        this->velocity.x += this->m_speed.x * dT;
        this->m_animTimer = 0.0f;       
        m_state = PlayerState::movingRight;
    }

    // Set the animation frame, may be moved in the future
    if (this->m_state == PlayerState::movingLeft || this->m_state == PlayerState::movingRight) {
        this->sprite->setTextureRect(m_animations[((int)(this->m_animTimer * 12) % 6)]);
    }

    if(m_controller->jump()) {
		jump(dT);
	}
    if (velocity.y < -FLT_EPSILON) {
        m_state = PlayerState::falling;
    }
}

void Player::update(float dT)
{
    //std::cout << (int)m_state << std::endl;
	if (m_controller != nullptr) {
        switch (m_state) {
        case PlayerState::movingLeft:
        case PlayerState::movingRight:
            move(dT);
            break;
        case PlayerState::jumping:
            jump(dT);
            break;
        case PlayerState::idle:
            idle(dT);
            break;
        case PlayerState::falling:
            fall(dT);
			break;
        }

        //this->state = State::iddle;
        if (m_controller->up()) {
            //move(glm::vec2(0, 1));
            this->velocity.y += this->m_speed.y * dT;
        }
        if (m_controller->down()) {
            //move(glm::vec2(0, -1));
            this->velocity.y -= this->m_speed.y * dT;
        }

        
        /*if (this->m_state == PlayerState::jumping) {
			
		}
		else if(m_state == PlayerState::idle) {
			this->sprite->setTextureRect(sf::IntRect(0, 0, 32, 32));
		}*/

        // Flip sprite when velocity change direction
        sf::Vector2f s = sprite->getScale();

        if ((velocity.x < 0 && s.x > 0) || (velocity.x > 0 && s.x < 0)) {
            this->sprite->setScale(-s.x, s.y);
        }

        if (velocity.x > speedCap.x) {
            velocity.x = speedCap.x;
        }
        else if (velocity.x < -speedCap.x) {
            velocity.x = -speedCap.x;
        }

        if (velocity.y > speedCap.y) {
            velocity.y = speedCap.y;
        }
        else if (velocity.y < -speedCap.y) {
            velocity.y = -speedCap.y;
        }

        velocity.y -= gravity * dT;

        position += velocity;

        // Call the parent update function
	    //Pawn::update(dT);

        // Check if the player is on the ground after the position update
        /*if (this->velocity.y >= -0.01f && this->velocity.y <= 0.01f && m_controller != nullptr) {
            if (!m_controller->jump()) {
			    m_jumping = false;
                this->m_state = PlayerState::idle;
		    }
	    }*/
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
