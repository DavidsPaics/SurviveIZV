#pragma once

#include <SFML/Graphics.hpp>
#include "Utils/TextureManager.hpp"
#include <vector>

class World;

class Entity{
public:
    Entity(World& worldRef);

    virtual void update(float deltaTime);
    virtual sf::Sprite& getSprite();

    sf::Vector2f getPosition() { return position; }
    sf::Vector2f getVelocity() { return velocity; }
    void setPosition(const sf::Vector2f& pos) {position = pos;}

protected:
    sf::Sprite sprite;
    sf::Vector2f position {0.f,0.f};
    sf::Vector2f velocity {0.f,0.f};

    World& world;

    sf::Vector2f movementDirection = {0,0};

    void resolveCollisions(const sf::Vector2f& delta);

    float terminalVelocity = 5.f;
};