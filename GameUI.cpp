#include "GameUI.h"

#include <iostream>

GameUI::GameUI()
{
	display = Display::Instance();
	if (!m_font.loadFromFile("./font/arial.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	m_debug_tickrate = new sf::Text();
	m_debug_tickrate->setPosition(0, 128);
	m_debug_tickrate->setCharacterSize(24);
	m_debug_tickrate->setFillColor(sf::Color::Red);
	m_debug_tickrate->setFont(m_font);

	display->addUITxt(m_debug_tickrate);
}

GameUI::~GameUI()
{
	if(m_debug_playerX != nullptr)
		delete m_debug_playerX;
	if (m_debug_playerY != nullptr)
		delete m_debug_playerY;
	if (m_debug_playerVX != nullptr)
		delete m_debug_playerVX;
	if (m_debug_playerVY != nullptr)
		delete m_debug_playerVY;
	if(m_debug_tickrate != nullptr)
		delete m_debug_tickrate;
}

//void GameUI::addDebugValue(std::string name, float* variable, glm::vec2 pos)
//{
//	DebugText* txt = new DebugText(name, variable, pos);
//	txt->uiTxt->setPosition(pos.x, pos.y + m_debugTxt.size() * 25);
//	txt->uiTxt->setFont(m_font);
//	txt->uiTxt->setCharacterSize(24);
//	txt->uiTxt->setFillColor(sf::Color::White);
//
//	m_debugTxt.push_back(txt);
//	display->addUITxt(txt->uiTxt);
//}

void GameUI::removeDebugText(sf::Text* txt)
{
}

void GameUI::clearDebugText()
{
}

void GameUI::update(float deltaT)
{
	/*for (auto &txt : m_debugTxt)
	{
		
	}*/
	if (m_showDebug && m_player != nullptr) {
		m_debug_playerX->setString("Player x: " + std::to_string(m_player->getPosition().x));
		m_debug_playerY->setString("Player y: " + std::to_string(m_player->getPosition().y));
		m_debug_playerVX->setString("Player vx: " + std::to_string(m_player->getVelocity().x));
		m_debug_playerVY->setString("Player vy: " + std::to_string(m_player->getVelocity().y));
		m_debug_tickrate->setString("Tick Rate: " + std::to_string(deltaT*1000000 ));
		m_debug_animTimer->setString("Anim Timer: " + std::to_string((((int)m_player->getAnimTimer() * 12) % 6)));
	}
}

void GameUI::toggleDebug()
{
	m_showDebug = !m_showDebug;
}

void GameUI::setPlayer(Player* player)
{
	m_player = player;
	m_debug_playerX = new sf::Text();
	m_debug_playerY = new sf::Text();
	m_debug_playerVX = new sf::Text();
	m_debug_playerVY = new sf::Text();
	m_debug_animTimer = new sf::Text();

	m_debug_playerX->setPosition(0, 0);
	m_debug_playerY->setPosition(0, 25);
	m_debug_playerVX->setPosition(0, 50);
	m_debug_playerVY->setPosition(0, 75);
	m_debug_animTimer->setPosition(0, 100);

	m_debug_playerX->setFont(m_font);
	m_debug_playerY->setFont(m_font);
	m_debug_playerVX->setFont(m_font);
	m_debug_playerVY->setFont(m_font);
	m_debug_animTimer->setFont(m_font);

	m_debug_playerX->setCharacterSize(24);
	m_debug_playerY->setCharacterSize(24);
	m_debug_playerVX->setCharacterSize(24);
	m_debug_playerVY->setCharacterSize(24);
	m_debug_animTimer->setCharacterSize(24);

	m_debug_playerX->setFillColor(sf::Color::White);
	m_debug_playerY->setFillColor(sf::Color::White);
	m_debug_playerVX->setFillColor(sf::Color::White);
	m_debug_playerVY->setFillColor(sf::Color::White);
	m_debug_animTimer->setFillColor(sf::Color::White);

	display->addUITxt(m_debug_playerX);
	display->addUITxt(m_debug_playerY);
	display->addUITxt(m_debug_playerVX);
	display->addUITxt(m_debug_playerVY);
	display->addUITxt(m_debug_animTimer);
}
