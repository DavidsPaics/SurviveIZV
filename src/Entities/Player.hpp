#pragma once

#include <SFML/Graphics.hpp>
#include "Entities/Entity.hpp"

class Player : public Entity {
public:
    Player();

    void handleEvent(sf::Event& event) {};

    void update(float deltaTime) override;
};