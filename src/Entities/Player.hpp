#pragma once

#include <SFML/Graphics.hpp>
#include "Entities/Entity.hpp"

class World;

class Player : public Entity {
public:
    Player(World& worldRef);

    void handleEvent(sf::Event& event) {};

    void update(float deltaTime) override;
};