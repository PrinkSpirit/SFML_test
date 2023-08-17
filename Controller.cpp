#include "Controller.h"


InputEvent::InputEvent()
{
}

InputEvent::InputEvent(std::initializer_list<sf::Keyboard::Key> input_keys) : m_input_keys(input_keys)
{
}


InputEvent::~InputEvent()
{
}

bool InputEvent::down()
{
	return m_down;
}

bool InputEvent::held()
{
	return m_held;
}

bool InputEvent::up()
{
	return m_up;
}

void InputEvent::update()
{
	bool down = false;

	for(auto key : m_input_keys)
	{
		down |= sf::Keyboard::isKeyPressed(key);
	}

	m_down = down && !m_held;	// Was 0, is now 1
	m_up = !down && m_held;		// Was 1, is now 0
	m_held = down;				// Is at 1
}

Controller::Controller() {
	m_actionMap["Up"] = InputEvent({ sf::Keyboard::Up, sf::Keyboard::W });
	m_actionMap["Down"] = InputEvent({ sf::Keyboard::Down, sf::Keyboard::S });
	m_actionMap["Left"] = InputEvent({ sf::Keyboard::Left, sf::Keyboard::A });
	m_actionMap["Right"] = InputEvent({ sf::Keyboard::Right, sf::Keyboard::D });

	m_actionMap["Attack"] = InputEvent({ sf::Keyboard::Z, sf::Keyboard::J });
	m_actionMap["Jump"] = InputEvent({ sf::Keyboard::Space, sf::Keyboard::K });
}

Controller::~Controller() {
	m_actionMap.clear();
}

InputEvent& Controller::operator[](std::string action)
{
	return m_actionMap[action];
}



void Controller::listen(sf::Event event)
{
	// We only update if we detect a key event
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyReleased || event.type == sf::Event::JoystickButtonReleased) {
		for (auto& const action : m_actionMap)
		{
			action.second.update();
		}
	}
}
