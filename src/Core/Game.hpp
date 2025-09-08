#include <SFML/Graphics.hpp>
#pragma once

class Game {
public:
    Game(sf::RenderWindow &window);
    void run();

private:
    void handleEvents();

private:
    sf::RenderWindow& window;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Clock clock;
};