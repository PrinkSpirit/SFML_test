#include "Player.h"

Player::Player() : Pawn()
{
}

Player::Player(glm::vec2 pos, const sf::Texture& texture) : Pawn(pos, texture)
{
	m_speed = glm::vec2(100.0f,200.0f); // Speed, magic number.

    m_states["Idle"] =          new CanFall<CanCrouch<CanMove<CanWalk<CanJump<CanAttack<Idle>>>>>>{this};
    m_states["Walk"] =          new CanFall<CanMove<CanCrouch<CanJump<CanAttack<Walk>>>>>{this};
    m_states["Jump"] =          new CanFall<CanMove<CanAttack<Jump>>>{this};
    m_states["Crouch"] =        new CanFall<CanJump<Crouch>>{this};
    m_states["Attack"] =        new CanFall<Attack>{this};
    m_states["CrouchStab"] =    new CanFall<CrouchStab>{this};
    

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
        /*if (m_controller->down()) {
            this->velocity.y -= this->m_speed.y * dT;
        }*/


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
	m_player->sprite->setTextureRect(m_animationSequence[0]);
}

void Player::Walk::out(float dT)
{

}

void Player::Walk::update(float dT)
{
    // If the player is moving, play the walk animation
    if (m_player->velocity.x < -FLT_EPSILON || m_player->velocity.x > FLT_EPSILON) {
	    m_animationTimer += dT;

		m_player->sprite->setTextureRect(m_animationSequence[((int)(m_animationTimer * 12) % 6)]);
	} 
    // If the player is not moving since 2 seconds, switch to idle
    else { 
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


/* ********** ********** ********** ********** ********** */
/*                         Crouch                         */
/* ********** ********** ********** ********** ********** */

Player::Crouch::Crouch(Player* player) : PlayerState(player), m_spriteRect(2 * 32, 32, 32, 32)
{

}

Player::Crouch::~Crouch()
{
}
void Player::Crouch::in(float dT)
{
	m_player->sprite->setTextureRect(m_spriteRect);
    // Make player smaller
}

void Player::Crouch::out(float dT)
{
	// Restore player size
}

void Player::Crouch::update(float dT)
{
    if (!m_player->getController()->down()) {
		m_player->switchState("Idle");
	} 
    if (m_player->getController()->down() && m_player->getController()->attack()) {
		m_player->switchState("CrouchStab");
	}
}

/* ********** ********** ********** ********** ********** */
/*                         Attack                         */
/* ********** ********** ********** ********** ********** */

Player::Attack::Attack(Player* player) : PlayerState(player),
    m_animationSequence({
        sf::IntRect(0, 32, 32, 32),     // Attack 1
        sf::IntRect(32, 32, 32, 32), // Attack 2
    })
{
}

Player::Attack::~Attack() {
}

void Player::Attack::in(float dT) {
    m_player->sprite->setTextureRect(m_animationSequence[0]);
    m_animationTimer = 0.1f;
    // Enable hitbox
}

void Player::Attack::out(float dT) {
    // Disable hitbox
}

void Player::Attack::update(float dT) {
    m_animationTimer += dT;

    if (m_animationTimer >= 0.7f) {
		m_player->switchState("Idle");
	}
    else {
		m_player->sprite->setTextureRect(m_animationSequence[((int)(m_animationTimer * 4) % 2)]);
	}
}

/* ********** ********** ********** ********** ********** */
/*                       Crouch Stab                      */
/* ********** ********** ********** ********** ********** */

Player::CrouchStab::CrouchStab(Player* player) : PlayerState(player),
    m_animationSequence({
		sf::IntRect(64, 32, 32, 32), // Attack 1
		sf::IntRect(96, 32, 32, 32), // Attack 2
	})
{

}

Player::CrouchStab::~CrouchStab() {
    
}

void Player::CrouchStab::in(float dT) {
    m_player->sprite->setTextureRect(m_animationSequence[0]);
    m_animationTimer = 0.1f;
    // Enable hitbox
}

void Player::CrouchStab::out(float dT) {
    // Disable hitbox
}

void Player::CrouchStab::update(float dT) {
    m_animationTimer += dT;

    if (m_animationTimer >= 0.7f) {
        m_player->switchState("Crouch");
    }
    else {
        m_player->sprite->setTextureRect(m_animationSequence[((int)(m_animationTimer * 4) % 2)]);
    }
}

