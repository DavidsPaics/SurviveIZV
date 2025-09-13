#include <SFML/Graphics.hpp>
#include "Core/World.hpp"
#pragma once

class Game {
public:
    Game(sf::RenderWindow &window);
    void run();

private:
    void handleEvents();
    void handleResize();

private:
    sf::RenderWindow& window;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    World world;
};