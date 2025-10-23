#include <Entities/InfectedPelmenis.hpp>
#include <Core/World.hpp>

InfectedPelmenis::InfectedPelmenis(World& worldRef) : Entity(worldRef){
    sprite.setTexture(TextureManager::getInstance().getTexture("entities/pelmenis"));

    lungeDuration.stop();
}

void InfectedPelmenis::update(float deltaTime){
    if (lungeClock.getElapsedTime().asSeconds() > 1.05f){
        lungeClock.restart();
        lungeDuration.restart();
        if ((world.getPlayer().getPosition() - position).length()>0)
            movementDirection = (world.getPlayer().getPosition() - position).normalized();
        else
            movementDirection={0,0};
    }
    if (lungeDuration.isRunning() && lungeDuration.getElapsedTime().asSeconds()>0.4f){
        lungeDuration.reset();
    }

    if (!lungeDuration.isRunning())
        movementDirection = {0,0};


    // movementDirection = (world.getPlayer().getPosition() - position).normalized();
    Entity::update(deltaTime);
}