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

    sf::RenderWindow window(sf::VideoMode(800, 600), "Zelda II - Clone");

    Controller controller;
    
    
    sf::Texture brickTexture;
    sf::Sprite* brickSprite;

    std::vector<sf::Sprite*> renderList;


    if (!brickTexture.loadFromFile("./sprites/brick.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
	}

    float rez = static_cast<float>(window.getSize().y) / brickTexture.getSize().y / 16.0f;

    for (int i = 0; i < 22; i++) {
        brickSprite = new sf::Sprite();
        brickSprite->setTexture(brickTexture);
        brickSprite->setScale(sf::Vector2f(rez, rez));
        brickSprite->setPosition(sf::Vector2f(16.0f * rez * i, window.getSize().y - 16.0f * rez));

        renderList.push_back(brickSprite);
    }

    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            controller.listen(event);
            if (event.type == sf::Event::Closed)
                window.close();

            if(controller.jump()) {
                std::cerr << "Jump " << std::endl;
                brickTexture.setSmooth(!brickTexture.isSmooth());
            }
            if (controller.down()) {
                std::cerr << "Down " << std::endl;
            }
                
        }

        window.clear();
        for (auto sprite : renderList) {
            window.draw(*sprite);
        }
        window.display();
    }

    std::for_each(renderList.begin(), renderList.end(), [](auto s) {delete s; });
    renderList.clear();

    return 0;
}