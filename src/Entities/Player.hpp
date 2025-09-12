#pragma once

#include <SFML/Graphics.hpp>
#include "Utils/TextureManager.hpp"
#include <vector>

class Player{
public:
    Player();

    void update(float deltaTime);
    sf::Sprite& getSprite();

    void handleEvent(sf::Event& event);

    sf::Vector2f getPosition() { return position; }
    sf::Vector2f getVelocity() { return velocity; }
    void setPosition(const sf::Vector2f& pos) {position = pos;}

    void setMap(std::vector<int>* mapData, sf::Vector2u newMapSize){
        mapPointer = mapData;
        mapSize = newMapSize;
    };

private:
    sf::Sprite sprite;
    sf::Vector2f position {0.f,0.f};
    sf::Vector2f velocity {0.f,0.f};

    std::vector<int>* mapPointer = nullptr;
    sf::Vector2u mapSize = {0,0};

    void resolveCollisions(const sf::Vector2f& delta);

    float terminalVelocity = 5.f;
};