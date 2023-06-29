#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include <iostream>
#include <vector>

#include "Display.h"
#include "Controller.h"

#include "Level.h"
#include "StaticObject.h"
#include "Actor.h"

int main()
{
    //3440 x 1440

    //sf::RenderWindow window(sf::VideoMode(800, 600), "Zelda II - Clone");

    Controller controller;
    Display* display =  Display::Instance();
    
    for (int i = 0; i < 22; i++) {

        BlockFactory::Instance()->createStaticObject(BlockType::Brick, glm::vec2(i, 0));
    }

    BlockFactory::Instance()->createStaticObject(BlockType::Brick, glm::vec2(0, 4));

    display->setBackgroundColor(sf::Color(92, 148, 252, 255));

    display->start();
    while (display->isWindowOpen())
    {
        sf::Event event;
        while (display->getWindow()->pollEvent(event))
        {
            controller.listen(event);
            if (event.type == sf::Event::Closed){
                display->stop();
            }

            if(controller.jump()) {
                //std::cerr << "Jump " << std::endl;
                std::cout << display->getWindow()->getSize().x/2 << "x" << display->getWindow()->getSize().y/2 << std::endl;
            }
            if (controller.down()) {
                std::cerr << "Down " << std::endl;
            }
                
        }
    }

    return 0;
}