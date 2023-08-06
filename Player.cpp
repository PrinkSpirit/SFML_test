#include "Player.h"

Player::Player() : Pawn()
{
}

Player::Player(glm::vec2 pos, const sf::Texture& texture) : Pawn(pos, texture)
{
	m_speed = glm::vec2(100.0f,200.0f); // Speed, magic number.

    m_states["Idle"] = new CanFall<CanMove<CanWalk<CanJump<Idle>>>>{this};
    m_states["Walk"] = new CanFall<CanMove<CanJump<Walk>>>{this};
    m_states["Jump"] = new CanFall<CanMove<Jump>>{this};

    // Default state
    m_state = m_states["Idle"];
    m_state->in(0.0f);

    // Hurtbox
    this->size = { sprite->getTextureRect().width / 1.33, sprite->getTextureRect().height};
    this->sprite->setOrigin(size.x/2.0f, size.y/2.0f);
}

//Player::Player(glm::vec2 pos, glm::vec2 size, const sf::Texture& texture) : Pawn(pos, size, texture)
//{
//}

Player::~Player()
{
}

void Player::update(float dT)
{
	if (m_controller != nullptr) {
        //Cheat code
        if (m_controller->up()) {
            this->velocity.y += this->m_speed.y * dT;
        }
        if (m_controller->down()) {
            this->velocity.y -= this->m_speed.y * dT;
        }


        m_state->update(dT);

        // Applying velocity cap
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

        position += velocity;

        // Call the parent update function
	    //Pawn::update(dT);

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

Player::PlayerState::PlayerState(Player* player) : m_player(player)
{
}

Player::PlayerState::~PlayerState()
{
    m_player = nullptr;
}


/* ********** ********** ********** ********** ********** */
/*                          Idle                          */
/* ********** ********** ********** ********** ********** */
Player::Idle::Idle(Player* player) : PlayerState(player), m_spriteRect(0, 0, 32, 32)
{
    
}


Player::Idle::~Idle()
{

}


void Player::Idle::in(float dT)
{
    m_player->sprite->setTextureRect(m_spriteRect);
}

void Player::Idle::update(float dT)
{
}

void Player::Idle::out(float dT)
{

}
/* ********** ********** ********** ********** ********** */
/*                          Walk                          */
/* ********** ********** ********** ********** ********** */

Player::Walk::Walk(Player* player) : PlayerState(player),
    m_animationSequence({
        sf::IntRect(0,0,32,32),     // Walk 1
        sf::IntRect(64,0,32,32),    // Walk 2
        sf::IntRect(96, 0, 32, 32), // Walk 3
        sf::IntRect(32, 0, 32, 32), // Walk 4
        sf::IntRect(64, 0, 32, 32), // Walk 5
        sf::IntRect(96, 0, 32, 32)  // Walk 6
    })
{

}

Player::Walk::~Walk()
{

}

void Player::Walk::in(float dT)
{
    m_animationTimer = 0.0f;
    m_idleTimer = 0.0f;
	m_player->sprite->setTextureRect(m_animationSequence[0]);
}

void Player::Walk::out(float dT)
{

}

void Player::Walk::update(float dT)
{
    // If the player is moving, play the walk animation
    if (m_player->velocity.x < -FLT_EPSILON || m_player->velocity.x > FLT_EPSILON) {
        m_idleTimer = 0.0f;
	    m_animationTimer += dT;

		m_player->sprite->setTextureRect(m_animationSequence[((int)(m_animationTimer * 12) % 6)]);
	} 
    // If the player is not moving since 2 seconds, switch to idle
    else if(m_idleTimer >= 2.0f) { 
        m_idleTimer += dT;

        if (dT >= 2.0f) {
            m_player->switchState("Idle");
            return;
        }
    }
}

/* ********** ********** ********** ********** ********** */
/*                          Jump                          */
/* ********** ********** ********** ********** ********** */

Player::Jump::Jump(Player* player) : PlayerState(player), 
    m_spriteRect(96, 0, 32, 32), m_jumpMaxDuration(.1f)
{
}

Player::Jump::~Jump()
{
}

void Player::Jump::in(float dT)
{
    m_player->sprite->setTextureRect(m_spriteRect);
	//m_player->velocity.y = m_player->m_speed.y / 7500.0f;
	
    m_player->m_jumping = true;
    m_player->m_grounded = false;

    m_jumpHeldTimer = 0.0f;    
    m_jumpHeld = true;
}

void Player::Jump::out(float dT)
{
	m_player->m_jumping = false;
}

void Player::Jump::update(float dT)
{
    // If the player is jumping for more than 4 seconds, or is no longer 
    // holding the jump button, he will stop rising
    if (m_jumpHeldTimer > m_jumpMaxDuration || !m_player->getController()->jump()) {
        m_jumpHeld = false;
        m_player->m_jumping = false;
    }
	// Else if the jump button is held, the player will jump higher
    else if (m_jumpHeldTimer <= m_jumpMaxDuration && m_player->getController()->jump() && m_jumpHeld) {
        m_jumpHeldTimer += dT;
		m_player->velocity.y = m_player->m_speed.y * dT;
	}

    if (m_player->velocity.y >= -FLT_EPSILON && m_player->velocity.y <= FLT_EPSILON) {
        m_player->m_grounded = true;
        m_player->switchState("Idle");
    }
}


