#include "Entities/Player.hpp"
#include "Utils/logging.hpp"
#include <SFML/Graphics.hpp>
#include "Utils/TextureManager.hpp"

Player::Player(): sprite(TextureManager::getInstance().getTexture("test")) {}

void Player::update(float deltaTime)
{
    position += velocity * deltaTime;
    sprite.setPosition(position);
}

sf::Sprite* Player::getSprite()
{
    return &sprite;
}

void Player::handleEvent(sf::Event& event) {}