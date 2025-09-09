#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entities/Player.hpp"

//TODO: FIX, This is a placeholder

class World {
public:
    World();

    void update(float deltaTime);
    void render(sf::RenderTarget& target);

private:
    Player myplayer;
};