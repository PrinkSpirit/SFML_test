#include "Controller.h"


Controller::Controller() {
	upInput.push_back(sf::Keyboard::Up);
	downInput.push_back(sf::Keyboard::Down);
	leftInput.push_back(sf::Keyboard::Left);
	rightInput.push_back(sf::Keyboard::Right);

	attackInput.push_back(sf::Keyboard::Z);
	jumpInput.push_back(sf::Keyboard::Space);
}

Controller::~Controller() {
	upInput.clear();
	downInput.clear();
	leftInput.clear();
	rightInput.clear();

	attackInput.clear();
	jumpInput.clear();
}

bool Controller::up()
{
	return _up;
}

bool Controller::down()
{
	return _down;
}

bool Controller::left()
{
	return _left;
}

bool Controller::right()
{
	return _right;
}

bool Controller::attack()
{
	return _attack;
}

bool Controller::jump()
{
	return _jump;
}

void Controller::listen(sf::Event event)
{

	
	if (event.type ==  sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed) {
		std::for_each(upInput.begin(), upInput.end(), [&](sf::Keyboard::Key key) {
			if (sf::Keyboard::isKeyPressed(key)) {
				this->_up = true;
			}
		});
		std::for_each(downInput.begin(), downInput.end(), [&](sf::Keyboard::Key key) {
			if (sf::Keyboard::isKeyPressed(key)) {
				this->_down = true;
			}
		});
		std::for_each(leftInput.begin(), leftInput.end(), [&](sf::Keyboard::Key key) {
			if (sf::Keyboard::isKeyPressed(key)) {
				this->_left = true;
			}
		});
		std::for_each(rightInput.begin(), rightInput.end(), [&](sf::Keyboard::Key key) {
			if (sf::Keyboard::isKeyPressed(key)) {
				this->_right = true;
			}
		});

		std::for_each(jumpInput.begin(), jumpInput.end(), [&](sf::Keyboard::Key key) {
			if (sf::Keyboard::isKeyPressed(key)) {
				this->_jump = true;
			}
		});
		std::for_each(attackInput.begin(), attackInput.end(), [&](sf::Keyboard::Key key) {
			if (sf::Keyboard::isKeyPressed(key)) {
				this->_attack = true;
			}
		});
	}

	if (event.type == sf::Event::KeyReleased || event.type == sf::Event::JoystickButtonReleased) {
		std::for_each(upInput.begin(), upInput.end(), [&](sf::Keyboard::Key key) {
			if (event.key.code == key) {
				this->_up = false;
			}
		});
		std::for_each(downInput.begin(), downInput.end(), [&](sf::Keyboard::Key key) {
			if (event.key.code == key) {
				this->_down = false;
			}
		});
		std::for_each(leftInput.begin(), leftInput.end(), [&](sf::Keyboard::Key key) {
			if (event.key.code == key) {
				this->_left = false;
			}
		});
		std::for_each(rightInput.begin(), rightInput.end(), [&](sf::Keyboard::Key key) {
			if (event.key.code == key) {
				this->_right = false;
			}
		});

		std::for_each(jumpInput.begin(), jumpInput.end(), [&](sf::Keyboard::Key key) {
			if (event.key.code == key) {
				this->_jump = false;
			}
		});
		std::for_each(attackInput.begin(), attackInput.end(), [&](sf::Keyboard::Key key) {
			if (event.key.code == key) {
				this->_attack = false;
			}
		});
		
	}
}