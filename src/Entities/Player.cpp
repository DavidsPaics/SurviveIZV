#include "Entities/Player.hpp"
#include "Utils/logging.hpp"
#include <SFML/Graphics.hpp>
#include "Utils/TextureManager.hpp"
#include "Utils/globals.hpp"
Player::Player(World& worldRef) : Entity(worldRef) {
    Entity::sprite.setTexture(TextureManager::getInstance().getTexture("entities/player"));
}


void Player::update(float deltaTime)
{
    // --- Input Acceleration ---
    Entity::movementDirection = {0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) Entity::movementDirection.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) Entity::movementDirection.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) Entity::movementDirection.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) Entity::movementDirection.x += 1.f;

    Entity::update(deltaTime);
}