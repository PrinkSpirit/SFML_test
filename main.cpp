#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "Display.h"
#include "Controller.h"

#include "Level.h"
#include "StaticObject.h"
#include "Actor.h"
#include "GameUI.h"

int main()
{
    //3440 x 1440

    //sf::RenderWindow window(sf::VideoMode(800, 600), "Zelda II - Clone");

    Controller controller;
    Display* display =  Display::Instance();
    Level level;
    GameUI ui;

    sf::Clock clock;
    sf::Time currentTime, lastTime;
    float fps = 0.0f;
    float dT = 0.0f;
    
    level.testLevel();
    level.getPlayer()->setController(&controller);
    ui.setPlayer(level.getPlayer());

    display->start();
    currentTime = lastTime = clock.restart();
    while (display->isWindowOpen())
    {
        sf::Event event;
        while (display->getWindow()->pollEvent(event))
        {
            controller.listen(event);
            if (event.type == sf::Event::Closed){
                display->stop();
            }
            if (event.type == sf::Event::Resized) {
				display->getWindow()->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}
            if(event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::LAlt || event.key.code == sf::Keyboard::RAlt){
					display->toggleDebug();
				}
			}
        }
        
        dT = clock.restart().asSeconds();
        level.update(dT);
        ui.update(dT);

        std::this_thread::sleep_for(std::chrono::seconds(1/60));
    }

    return 0;
}