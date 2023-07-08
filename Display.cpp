#include "Display.h"
#include <cstdlib>
#include <iostream>
#include <cmath>


// Singleton instance pointer is set to nullptr at the beginning
Display* Display::instance = nullptr; 

Display::Display() {
	this->window = new sf::RenderWindow(sf::VideoMode(nesWidth*4, nesHeight*4), "Zelda II - Clone");
	this->window->setActive(false);

	this->window->setFramerateLimit(this->frameRate);
	//this->window->setKeyRepeatEnabled(false);

	this->renderingThread = new sf::Thread(&threadedRendering, this);

	//this->spriteScale = sf::Vector2f(window->getSize().y / 16.0f / 16.0f, window->getSize().y / 16.0f / 16.0f);
	this->spriteScale = sf::Vector2f(window->getSize().y / nesHeight, window->getSize().y / nesHeight);
}

Display::~Display()
{
	// Wait for the rendering thread to stop
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
			sprite->setPosition(this->toScreenSpace(object->getPosition(), object->getSize()));

			this->window->draw((*object->getSprite()));
		}
		sprite = nullptr;
		if (showDebug){
			for(auto txt : this->UITxtList)
			{
				this->window->draw(*txt);
			}
		}
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

void Display::addUITxt(sf::Text* txt)
{
	sf::Lock lock(this->mutex);
	this->UITxtList.push_back(txt);
}

void Display::removeUITxt(sf::Text* txt)
{
	sf::Lock lock(this->mutex);
	this->UITxtList.erase(std::remove(this->UITxtList.begin(), this->UITxtList.end(), txt), this->UITxtList.end());
}

Display* Display::Instance()
{
	if (instance == nullptr) {
		instance = new Display();
		std::atexit(release);
	}

	return instance;
}

void Display::start() {
	if (!this->isRunning) {
		this->isRunning = true;
		this->renderingThread->launch();
	}
}

void Display::stop() {
	if (this->isRunning) {
		this->isRunning = false;
		this->renderingThread->wait();
		this->window->close();
	}
}

void releaseDisplay()
{
	Display::release();
}

void Display::release() {
	if (instance != nullptr) { // Insure that the instance exists
		delete(instance);
		instance = nullptr;
	}
}

bool Display::isWindowOpen()
{
	return this->window->isOpen();
}

sf::RenderWindow* Display::getWindow()
{
	return this->window;
}

void Display::setBackgroundColor(sf::Color color)
{
	backgroundColor = color;
}

sf::Vector2f Display::toScreenSpace(glm::vec2 pos, glm::vec2 size)
{
	sf::Vector2f out;
	out.x = (int)((pos.x + size.x / 2.0f) * spriteScale.x);
	out.y = (int)(window->getSize().y - (pos.y + size.y/2.0f) * spriteScale.y);

	return out;
}

void Display::toggleDebug()
{
	this->showDebug = !this->showDebug;
}


void threadedRendering(Display* display) {
	display->parrallelRendering();
}
