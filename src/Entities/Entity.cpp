#include "Entities/Entity.hpp"
#include "Utils/logging.hpp"
#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Utils/TextureManager.hpp"
#include "Utils/globals.hpp"
#include "Core/Game.hpp"
#include "Utils/Math.hpp"
#include "Core/World.hpp"

Entity::Entity(World& worldRef) : sprite(TextureManager::getInstance().getTexture("error")), world(worldRef) {
    sprite.setTextureRect(sf::IntRect({0, 0}, {32,32}));
    sprite.setScale({globals::scalingFactor,globals::scalingFactor});
}


void Entity::update(float deltaTime)
{
    //Taken from player.cpp

    // --- Input Acceleration ---
    // movementDirection = {0,0};
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movementDirection.y -= 1.f;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movementDirection.y += 1.f;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movementDirection.x -= 1.f;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movementDirection.x += 1.f;

    if (movementDirection.length()>0)
        movementDirection = movementDirection.normalized();
    
    velocity += movementDirection * acceleration * deltaTime;
    
    velocity *= std::exp(-drag * deltaTime);

    // Optional: prevent tiny velocities from lingering
    if (std::abs(velocity.x) < minVelocity) velocity.x = 0.f;
    if (std::abs(velocity.y) < minVelocity) velocity.y = 0.f;


    // --- Clamp to terminal velocity ---
    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speed > maxVelocity) {
        velocity = (velocity / speed) * maxVelocity;
    }

    resolveCollisions({velocity.x * deltaTime,0});
    resolveCollisions({0,velocity.y * deltaTime});
    

    // logging::DEBUG("Velocity: (" + std::to_string(velocity.x) + ", " + std::to_string(velocity.y) + ")");
    // logging::DEBUG("Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")");

    sprite.setPosition(tilesToPixelsV2F(position));
}

sf::Sprite &Entity::getSprite()
{
    return sprite; // duh
}

void Entity::resolveCollisions(const sf::Vector2f& delta)
{
    float shrinkCollider=0.1f; //Shirnk the collider so that the shit fits thru the hole

    sf::Vector2f offset = {shrinkCollider,shrinkCollider};
    sf::Vector2f size = {1.f-shrinkCollider*2, 1.f-shrinkCollider*2};

    sf::Vector2f rectPos = position + offset;

    // --- Move along X axis ---
    rectPos.x += delta.x;

    int minX = std::floor(rectPos.x);
    int maxX = std::floor(rectPos.x + size.x);
    int minY = std::floor(rectPos.y);
    int maxY = std::floor(rectPos.y + size.y);

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            int tileIndex = y * world.getMapSize().x + x;
            if (world.getMapTileInfo()[(world.getMap())[tileIndex]].layer == 1) { // collidable tile
                sf::FloatRect tileRect({float(x), float(y)}, {1.f, 1.f});

                // Check intersection along X axis
                if (rectPos.y + size.y > tileRect.position.y && rectPos.y < tileRect.position.y + tileRect.size.y) {
                    if (delta.x > 0) // moving right
                        rectPos.x = tileRect.position.x - size.x;
                    else if (delta.x < 0) // moving left
                        rectPos.x = tileRect.position.x + tileRect.size.x;
                    //if delta==0, then everything is shit and not having collision is the smallest of your problems
                    // also floing points are bad, but nto that bad, so you will always have some direction , hopegully

                    //aksoi dont wanna do it
                }
            }
        }
    }

    //this is all spagetti, but asked chatGPT to refactor so it is a bitr better
    // kustība pa igrek asi


    rectPos.y += delta.y;

    minX = std::floor(rectPos.x);
    maxX = std::floor(rectPos.x + size.x);
    minY = std::floor(rectPos.y);
    maxY = std::floor(rectPos.y + size.y);

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            int tileIndex = y * world.getMapSize().x + x;
            if (world.getMapTileInfo()[(world.getMap())[tileIndex]].layer == 1) { // collidable tile
                sf::FloatRect tileRect({float(x), float(y)}, {1.f, 1.f});

                // Check intersection along Y axis
                if (rectPos.x + size.x > tileRect.position.x && rectPos.x < tileRect.position.x + tileRect.size.x) {
                    if (delta.y > 0) // moving down
                        rectPos.y = tileRect.position.y - size.y;
                    else if (delta.y < 0) // moving up
                        rectPos.y = tileRect.position.y + tileRect.size.y;
                }
            }
        }
    }

    position = rectPos - offset; //you get it
}
