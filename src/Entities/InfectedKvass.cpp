#include <Entities/InfectedKvass.hpp>
#include <Core/World.hpp>

InfectedKvass::InfectedKvass(World& worldRef) : Entity(worldRef){
    sprite.setTexture(TextureManager::getInstance().getTexture("entities/kvass"));

    terminalVelocity=0.5f;
    acceleration=500.f;
}

void InfectedKvass::update(float deltaTime){
        movementDirection = (world.getPlayer().getPosition() - position).normalized();
    Entity::update(deltaTime);
}