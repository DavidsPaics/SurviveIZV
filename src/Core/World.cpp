#include <SFML/Graphics.hpp>
#include "Core/World.hpp"
#include "Utils/logging.hpp"
#include "Entities/Player.hpp"

//TODO: This is a placeholder, FIX world.hpp first

World::World() : myplayer()
{

}

void World::update(float deltaTime)
{
    myplayer.update(deltaTime);
}

void World::render(sf::RenderTarget& target)
{
    target.draw(*myplayer.getSprite());
}