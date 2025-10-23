#include <Entities/InfectedSpageti.hpp>
#include "Utils/math.hpp"
#include <Core/World.hpp>



InfectedSpageti::InfectedSpageti(World& worldRef) : Entity(worldRef){
    sprite.setTexture(TextureManager::getInstance().getTexture("entities/spageti"));

    terminalVelocity=2.3f;
    acceleration=500.f;
}

void InfectedSpageti::update(float deltaTime){
    auto centerPosition = pixelsToTilesV2F(sprite.getGlobalBounds().getCenter());
    if(((isWithinRange(centerPosition.x,nextPos.x,0.1f) && isWithinRange(centerPosition.y,nextPos.y,0.1f))) || timeSincePathUpdate.getElapsedTime().asMilliseconds()>=500){
        timeSincePathUpdate.restart();
        nextPos = pathfind(sf::Vector2f(centerPosition),sf::Vector2f(world.getPlayer().getPosition()));
        if(sf::Vector2f(nextPos-centerPosition).length()>0)
            movementDirection = (nextPos - centerPosition).normalized();
    }
    Entity::update(deltaTime);
}