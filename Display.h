#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "GameObject.h"


class Display
{
protected:
	Display();
	static Display* instance;

	sf::RenderWindow* window;
	sf::Thread* renderingThread = nullptr;
	sf::Mutex mutex;
	bool isRunning = false;

	float frameRate = 60.0f;
	float nesWidth = 256.0f;
	float nesHeight = 240.0f;
	float spriteUnit = 16.0f;
	
	std::vector<GameObject*> renderList;

	sf::Vector2f spriteScale = sf::Vector2f(2.0f, 2.0f);
	sf::Color backgroundColor = sf::Color::Black;

	

public:
	~Display();

	static Display* Instance();

	void addSprite(GameObject*);
	void removeSprite(GameObject*);
	 
	bool start();
	bool stop();

	void rendering();
	void parrallelRendering();

	static void release();

	bool isWindowOpen();
	sf::RenderWindow* getWindow();

	void setBackgroundColor(sf::Color color);

	/**
	* \brief Convert a position in the world space to a position in the screen space.
	*/
	sf::Vector2f toScreenSpace(glm::vec2, glm::vec2);
};

void threadedRendering(Display* display);