#pragma once

#include <SFML/Graphics.hpp>
#include "Utils/TextureManager.hpp"

class Player{
public:
    Player();

    void update(float deltaTime);
    sf::Sprite* getSprite();

    void handleEvent(sf::Event& event);

private:
    sf::Sprite sprite;
    sf::Vector2f position {30.f,30.f};
    sf::Vector2f velocity {0.f,0.f};
};