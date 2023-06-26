#pragma once

#include <SFML/Graphics.hpp>
#include <vector>



class Controller
{
protected:
	std::vector<sf::Keyboard::Key> upInput;
	std::vector<sf::Keyboard::Key> downInput;
	std::vector<sf::Keyboard::Key> leftInput;
	std::vector<sf::Keyboard::Key> rightInput;

	std::vector<sf::Keyboard::Key> attackInput;
	std::vector<sf::Keyboard::Key> jumpInput;

	bool _up = false;
	bool _down = false;
	bool _left = false;
	bool _right = false;

	bool _attack = false;
	bool _jump = false;

public:
	Controller();
	~Controller();

	bool up();
	bool down();
	bool left();
	bool right();

	bool attack();
	bool jump();

	void listen(sf::Event);
};

