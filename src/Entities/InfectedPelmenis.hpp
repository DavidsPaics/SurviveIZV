#pragma once

#include <Entities/Entity.hpp>

class InfectedPelmenis : public Entity {
public:
    InfectedPelmenis(World& worldRef);
    void update(float deltaTime) override;

private:
    sf::Clock lungeClock;
    sf::Clock lungeDuration;
};