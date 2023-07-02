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

        BlockFactory::Instance()->createStaticObject(BlockType::Brick, glm::vec2(i*16, 0));
    }

    BlockFactory::Instance()->createStaticObject(BlockType::Brick, glm::vec2(0, 4*16));

    display->setBackgroundColor(sf::Color(92, 148, 252, 255));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("./sprites/linkSingle.bmp");

    Player player(glm::vec2(4*16, 4*16), playerTexture);
    //player.setSprite(playerTexture);
    display->addSprite(&player);


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
            if (event.type == sf::Event::Resized) {
				display->getWindow()->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}

            if(controller.jump()) {
                //std::cerr << "Jump " << std::endl;
                std::cout << display->getWindow()->getSize().x/2 << "x" << display->getWindow()->getSize().y/2 << std::endl;
            }

            if (controller.up()) {
                player.move(glm::vec2(0, 1));
			}
            if (controller.down()) {
                player.move(glm::vec2(0, -1));
            }
            if (controller.left()) {
    			player.move(glm::vec2(-1, 0));
			}
			if (controller.right()) {
                player.move(glm::vec2(1, 0));
            }

        }
        player.update();
    }

    return 0;
}