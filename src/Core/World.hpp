#pragma once
#include <SFML/Graphics.hpp>

//TODO: FIX, This is a placeholder

class World {
public:
    World();

    void update(float deltaTime);
    void render(sf::RenderTarget& target);
};