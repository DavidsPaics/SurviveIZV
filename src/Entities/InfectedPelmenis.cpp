#include <Entities/InfectedPelmenis.hpp>
#include <Core/World.hpp>

InfectedPelmenis::InfectedPelmenis(World& worldRef) : Entity(worldRef){
    sprite.setTexture(TextureManager::getInstance().getTexture("entities/pelmenis"));
    terminalVelocity = 70.f;
    acceleration = 1000.f;

    lungeDuration.stop();
}

void InfectedPelmenis::update(float deltaTime){
    if (lungeClock.getElapsedTime().asSeconds() > 1.5f){
        lungeClock.restart();
        lungeDuration.restart();
        movementDirection = (world.getPlayer().getPosition() - position).normalized();
    }
    if (lungeDuration.isRunning() && lungeDuration.getElapsedTime().asSeconds()>0.25f){
        lungeDuration.reset();
    }

    if (!lungeDuration.isRunning())
        movementDirection = {0,0};


    // movementDirection = (world.getPlayer().getPosition() - position).normalized();
    Entity::update(deltaTime);
}