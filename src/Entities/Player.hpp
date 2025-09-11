#pragma once

#include <SFML/Graphics.hpp>
#include "Utils/TextureManager.hpp"

class Player{
public:
    Player();

    void update(float deltaTime);
    sf::Sprite& getSprite();

    void handleEvent(sf::Event& event);

    sf::Vector2f getPosition() { return position; }

private:
    sf::Sprite sprite;
    sf::Vector2f position {3.f,3.f};
    sf::Vector2f velocity {0.f,0.f};

    float terminalVelocity = 10.f;
};