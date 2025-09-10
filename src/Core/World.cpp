#include <SFML/Graphics.hpp>
#include "Core/World.hpp"
#include "Utils/logging.hpp"
#include "Entities/Player.hpp"

//TODO: This is a placeholder, FIX world.hpp first

World::World() : player()
{
    
}

void World::update(float deltaTime)
{
    player.update(deltaTime);
}

void World::render(sf::RenderTarget& target)
{
    target.draw(player.getSprite());
}

void World::handleEvent(sf::Event& event)
{
    player.handleEvent(event);
}