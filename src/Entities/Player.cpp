#include "Entities/Player.hpp"
#include "Utils/logging.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Utils/TextureManager.hpp"

Player::Player() : sprite(TextureManager::getInstance().getTexture("player")) {
    sprite.setTextureRect(sf::IntRect({0, 0}, {32,32}));
}


void Player::update(float deltaTime)
{
    // --- Constants you can tweak ---
    const float acceleration = 2000.f;   // how fast you speed up
    const float drag = 5.f;              // how fast you slow down (lower = more slippery)
    const float minVelocity = 1.5f;      // cutoff to stop jitter
    const float maxVelocity = terminalVelocity;

    // --- Input Acceleration ---
    sf::Vector2f input({0.f, 0.f});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) input.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) input.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) input.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) input.x += 1.f;

    if (input.x != 0.f || input.y != 0.f) {
        float len = std::sqrt(input.x * input.x + input.y * input.y);
        input /= len; // normalize
        velocity += input * acceleration * deltaTime;
    }

    // --- Apply drag (linear friction, not exponential) ---
    if (velocity.x != 0.f || velocity.y != 0.f) {
        sf::Vector2f dragForce = -velocity * drag * deltaTime;
        velocity += dragForce;

        // prevent overshooting into negative
        if (std::abs(velocity.x) < minVelocity) velocity.x = 0.f;
        if (std::abs(velocity.y) < minVelocity) velocity.y = 0.f;
    }

    // --- Clamp to terminal velocity ---
    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speed > maxVelocity) {
        velocity = (velocity / speed) * maxVelocity;
    }

    // --- Move ---
    position += velocity * deltaTime;
    sprite.setPosition(position);

    // logging::DEBUG("Velocity: (" + std::to_string(velocity.x) + ", " + std::to_string(velocity.y) + ")");
}

sf::Sprite &Player::getSprite()
{
    return sprite;
}

void Player::handleEvent(sf::Event &event) {}