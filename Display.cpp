#include "Display.h"
#include <cstdlib>
#include <iostream>
#include <cmath>


Display* Display::instance = nullptr;

Display::Display() {
	this->window = new sf::RenderWindow(sf::VideoMode(256*4, 240*4), "Zelda II - Clone");
	this->window->setActive(false);

	this->window->setFramerateLimit(this->frameRate);

	this->renderingThread = new sf::Thread(&threadedRendering, this);

	//this->spriteScale = sf::Vector2f(window->getSize().y / 16.0f / 16.0f, window->getSize().y / 16.0f / 16.0f);
	this->spriteScale = sf::Vector2f(window->getSize().y / 256, window->getSize().y / 256);
}

Display::~Display()
{
	this->renderingThread->wait();
	delete(this->renderingThread);
	delete(this->window);
}


void Display::parrallelRendering() {
	this->window->setActive(true);
	while (isRunning) {
		this->rendering();
	}
}

void Display::rendering() {
	sf::Sprite* sprite = nullptr;

	this->window->clear(this->backgroundColor);

	try
	{
		for (auto object : this->renderList) {
			sprite = object->getSprite();

			// Updating sprites positions
			sprite->setPosition(this->toScreenSpace(object->getPosition()));

			this->window->draw((*object->getSprite()));
		}
		sprite = nullptr;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	this->window->display();
}

void Display::addSprite(GameObject* sprite) {
	sf::Lock lock(this->mutex); // Ensure that the sprite list is not modified during the addition
	sprite->getSprite()->setScale(spriteScale);
	this->renderList.push_back(sprite);
}

void Display::removeSprite(GameObject* sprite) {
	sf::Lock lock(this->mutex); // Ensure that the sprite list is not modified during the removal
	this->renderList.erase(std::remove(this->renderList.begin(), this->renderList.end(), sprite), this->renderList.end());
}

Display* Display::Instance()
{
	if (instance == nullptr) {
		instance = new Display();
		std::atexit(release);
	}

	return instance;
}

bool Display::start() {
	this->isRunning = true;
	this->renderingThread->launch();
	return true;
}

bool Display::stop() {
	this->isRunning = false;
	this->renderingThread->wait();
	this->window->close();
	return true;
}

void releaseDisplay()
{
	Display::release();
}

void Display::release() {
	delete(instance);
	instance = nullptr;
}

bool Display::isWindowOpen()
{
	return this->window->isOpen();
}

sf::Window* Display::getWindow()
{
	return this->window;
}

void Display::setBackgroundColor(sf::Color color)
{
	this->backgroundColor = color;
}

sf::Vector2f Display::toScreenSpace(glm::vec2 pos)
{
	sf::Vector2f out;
	out.x = pos.x * 16 * this->spriteScale.x;
	out.y = this->window->getSize().y - (pos.y + 1) * 16 * this->spriteScale.y;

	return out;
}


void threadedRendering(Display* display) {
	display->parrallelRendering();
}
