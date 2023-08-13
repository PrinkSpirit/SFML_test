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

	std::set<sf::Keyboard::Key> m_input_keys;

public:
	InputEvent();
	InputEvent(std::initializer_list<sf::Keyboard::Key>);
	~InputEvent();

	bool down();
	bool held();
	bool up();

	void update();
};

/// @brief Serve as an interface for the SFML keyboard and joysticks events
/// @todo Should be divided. One class contains a subclass that represent an action
class Controller
{
protected:
	std::unordered_map<std::string, InputEvent> m_actionMap;

	/// @brief The set contains the keys coresponding to each actions
	

public:
	Controller();
	~Controller();

	InputEvent& operator[](std::string);

	void listen(sf::Event);
};

