#include <Entities/InfectedKvass.hpp>
#include "Utils/math.hpp"
#include <Core/World.hpp>

/*
TODO: Figure out a good way to keep track of animation indicies

Current animations:
#0 - moving left (can also be up and down) (4 Frames)
*/

InfectedKvass::InfectedKvass(World& worldRef) : Entity(worldRef){
    sprite.setTexture(TextureManager::getInstance().getTexture("entities/kvass"));

    setupAnimations(2,{4});
    playLoopingAnimation(0);

    terminalVelocity=1.9f;
    acceleration=500.f;
}

void InfectedKvass::update(float deltaTime){
    auto centerPosition = pixelsToTilesV2F(sprite.getGlobalBounds().getCenter());
    if(((isWithinRange(centerPosition.x,nextPos.x,0.1f) && isWithinRange(centerPosition.y,nextPos.y,0.1f))) || timeSincePathUpdate.getElapsedTime().asMilliseconds()>=500){
        timeSincePathUpdate.restart();
        nextPos = pathfind(sf::Vector2f(centerPosition),sf::Vector2f(world.getPlayer().getPosition()));
        if(sf::Vector2f(nextPos-centerPosition).length()>0)
            movementDirection = (nextPos - centerPosition).normalized();
    }
    Entity::update(deltaTime);
}