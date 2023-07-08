#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "GameObject.h"

/// <summary>
/// Manage the display elements of the game.
/// Singleton.
/// </summary>
class Display
{
protected:
	Display();
	static Display* instance;				// Singleton instance of the class.

	sf::RenderWindow* window;				// SFML game window.
	sf::Thread* renderingThread = nullptr;	// Thread used to render the game.
	sf::Mutex mutex;						// Mutex used to lock secure data operation.
	bool isRunning = false;					// Whether the game is running or not.

	float frameRate = 60.0f;				// Frame rate of the game.
	float nesWidth = 256.0f;				// Width of the NES screen.
	float nesHeight = 240.0f;				// Height of the NES screen.
	float spriteUnit = 16.0f;				// Size of a basic sprite in the game. To be removed.

	bool showDebug = false;					// Whether the game should show debug information or not.	
	
	std::vector<GameObject*> renderList;	// List of all the GameObject to render.
	std::vector<sf::Text*> UITxtList;		// List of all the UI text to render.

	sf::Vector2f spriteScale = sf::Vector2f(2.0f, 2.0f); // Scale of the sprites. Default is x2.
	sf::Color backgroundColor = sf::Color::Black;		 // Background color of the game.

	

public:
	~Display();

	/// <summary>
	/// Return the singleton instance of the class.
	/// </summary>
	/// <returns>Pointer to the Display manager instance</returns>
	static Display* Instance();

	/// <summary>
	/// Add a GameObject to the rendering list.
	/// </summary>
	/// <param name="object">Pointer to a game object</param>
	void addSprite(GameObject*);

	/// <summary>
	/// Remove a GameObject from the rendering list.
	/// </summary>
	/// <param name="object">GameObject to be removed</param>
	void removeSprite(GameObject*);

	/// <summary>
	/// Add a UI text to the rendering list.
	/// </summary>
	/// <param name="text">Pointer to the sfml text to be displayed</param>
	void addUITxt(sf::Text*);

	/// <summary>
	/// Remove a UI text from the rendering list.
	/// </summary>
	/// <param name="text">Pointer to the sfml text to be removed</param>
	void removeUITxt(sf::Text*);

	/// <summary>
	/// Rendering of a single frame.
	/// Maybe should be made inline to save a function call?
	/// </summary>
	void rendering();

	/// <summary>
	/// Call the rendering loop in a parallel thread.
	/// </summary>
	void parrallelRendering();

	/// <summary>
	/// Start the rendering thread.
	/// </summary>
	/// <returns></returns>
	void start();
	void stop();

	/// <summary>
	/// Delete the instance of the singleton.
	/// Set to be called automatically at the end of the program.
	/// </summary>
	static void release();

	bool isWindowOpen();

	/// <summary>
	/// Return the pointer to the game window.
	/// </summary>
	/// <returns>pointer to sfml window</returns>
	sf::RenderWindow* getWindow();

	/// <summary>
	/// Change the color of the background.
	/// </summary>
	/// <param name="color">New color</param>
	void setBackgroundColor(sf::Color color);

	/// <summary>
	/// Convert a position in the world space to a position in the screen space, including
	/// offseting to the center of the element.
	/// </summary>
	/// <param name="position">Position in game space</param>
	/// <param name="size">Size of the element</param>
	/// <returns></returns>
	sf::Vector2f toScreenSpace(glm::vec2, glm::vec2);

	void toggleDebug();
};

/// <summary>
/// Call the rendering loop in a parallel thread.
/// Needs to be defined outside of the class but should not be called by the user.
/// </summary>
/// <param name="display">Pointer to the display manager</param>
void threadedRendering(Display* display);