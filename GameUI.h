#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Display.h"
#include "Player.h"


class GameUI
{
protected:
	Display* display;

	bool m_showDebug = true;
	sf::Font m_font;

	Player* m_player = nullptr;

	sf::Text* m_debug_playerX = nullptr;
	sf::Text* m_debug_playerY = nullptr;
	sf::Text* m_debug_playerVX = nullptr;
	sf::Text* m_debug_playerVY = nullptr;
	
	sf::Text* m_debug_animTimer = nullptr;

	sf::Text* m_debug_tickrate = nullptr;

public:
	GameUI();
	~GameUI();

	//void addDebugValue(std::string, float *variable, glm::vec2 pos);
	void removeDebugText(sf::Text* txt);
	void clearDebugText();

	void update(float);
	void toggleDebug();

	void setPlayer(Player* player);
};

