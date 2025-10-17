#include <Entities/InfectedKvass.hpp>
#include "Utils/math.hpp"
#include <Core/World.hpp>

InfectedKvass::InfectedKvass(World& worldRef) : Entity(worldRef){
    sprite.setTexture(TextureManager::getInstance().getTexture("entities/kvass"));

    terminalVelocity=3.f;
    acceleration=500.f;
}

void InfectedKvass::update(float deltaTime){
    if(((isWithinRange(position.x,nextPos.x,0.1f) && isWithinRange(position.y,nextPos.y,0.1f))) || timeSincePathUpdate.getElapsedTime().asMilliseconds()>=500){
        timeSincePathUpdate.restart();
        nextPos = pathfind(sf::Vector2f(position),sf::Vector2f(world.getPlayer().getPosition()));
        if(sf::Vector2f(nextPos-position).length()>0)
            movementDirection = (nextPos - position).normalized();
    }
    Entity::update(deltaTime);
}