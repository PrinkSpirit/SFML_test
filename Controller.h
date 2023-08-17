#pragma once

#include <SFML/Graphics.hpp>
#include <set>
#include <unordered_map>
#include <initializer_list>

class InputEvent
{
protected:
	bool m_down = false;	// true when key goes from up to down
	bool m_held = false;	// true when key is held down
	bool m_up	= false;	// true when key goes from down to up

	/// @brief The set contains the keys coresponding to this action
	std::set<sf::Keyboard::Key> m_input_keys;

public:
	InputEvent();
	InputEvent(std::initializer_list<sf::Keyboard::Key>);
	~InputEvent();

	bool down();
	bool held();
	bool up();

	/// @brief Check if any of the keys from m_input_keys are pressed
	void update();
};

/// @brief Serve as an interface for the SFML keyboard and joysticks events
/// @todo Should be divided. One class contains a subclass that represent an action
class Controller
{
protected:
	/// @brief Contains a list of actions and the InputEvent to handle the key presses
	std::unordered_map<std::string, InputEvent> m_actionMap;

public:
	Controller();
	~Controller();

	/// @brief Return the InputEvent for the action
	/// @param action Name of the action
	/// @return Reference to the input event
	InputEvent& operator[](std::string);

	/// @brief Update the InputEvent for each action
	/// @param event Event list from SFML
	void listen(sf::Event); 
};

