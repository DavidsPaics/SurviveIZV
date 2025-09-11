#include <SFML/Graphics.hpp>
#include "Core/World.hpp"
#include "Utils/logging.hpp"
#include "Entities/Player.hpp"
#include "Utils/globals.hpp"
#include <fstream>
#include <string>


World::World(const std::string map) : player(), tileSprite(TextureManager::getInstance().getTexture("tileset"))
{
    tileSprite.setTextureRect(sf::IntRect({0,0},{32,32}));
    tileSprite.setScale({globals::scalingFactor,globals::scalingFactor});
    loadMap(map);

}

void World::update(float deltaTime)
{
    player.update(deltaTime);
}

void World::render(sf::RenderTarget& target)
{
    // Draw the tile map
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            char tileType = mapData[y * mapWidth + x];
            if (tileType != 0) { // Assuming 0 is empty space
                tileSprite.setTextureRect(sf::IntRect({(tileType-1)*32,0},{32,32}));
                tileSprite.setPosition({(x * 32 * globals::scalingFactor),(y * 32 * globals::scalingFactor)});
                target.draw(tileSprite);
            }
        }
    }

    target.draw(player.getSprite());
}

void World::handleEvent(sf::Event& event)
{
    player.handleEvent(event);
}

void World::loadMap(const std::string& name)
{
    std::ifstream file("assets/maps/" + name + ".izv-map");

    if (!file.is_open()) {
        logging::ERROR("Failed to open map file: " + name);
        return;
    }

    file >> mapWidth >> mapHeight;
    mapData.resize(mapWidth * mapHeight);

    int mult, tile;
    int index = 0; // position in mapData

    while (file >> mult >> tile && index < mapWidth * mapHeight) {
        for (int n = 0; n < mult && index < mapWidth * mapHeight; n++) {
            mapData[index++] = tile;
        }
    }

    logging::DEBUG("Loaded map " + name);
}
