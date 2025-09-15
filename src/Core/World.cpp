#include <SFML/Graphics.hpp>
#include "Core/World.hpp"
#include "Utils/logging.hpp"
#include "Entities/Player.hpp"
#include "Utils/globals.hpp"
#include "Game/Camera.hpp"
#include "Utils/Math.hpp"
#include <fstream>
#include <set>
#include <string>

World::World(const std::string map) : player(*this), tileSprite(TextureManager::getInstance().getTexture("tileset"))
{
    tileSprite.setTextureRect(sf::IntRect({0,0},{32,32}));
    tileSprite.setScale({globals::scalingFactor,globals::scalingFactor});
    loadMap(map);
}

void World::update(float deltaTime)
{
    player.update(deltaTime);
}

void World::render(sf::RenderTarget& target, Camera& camera)
{
    auto center = camera.getView().getCenter();
    auto size = camera.getView().getSize();
    sf::Vector2f topLeft = {pixelsToTiles(center.x-size.x/2.f), pixelsToTiles(center.y-size.y/2.f)};
    sf::Vector2f bottomRight = topLeft + pixelsToTilesV2F(size);
    if (topLeft.x <0)
        topLeft.x=0;
    if (topLeft.y<0)
        topLeft.y=0;

    if (bottomRight.y>=mapHeight)
        bottomRight.y = mapHeight-1;
    if (bottomRight.x>=mapWidth)
        bottomRight.x = mapWidth-1;

    // logging::DEBUG(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);

    // Draw the tile map
    for (int y = static_cast<int>(topLeft.y); y < static_cast<int>(bottomRight.y+1); ++y) {
        for (int x = static_cast<int>(topLeft.x); x < static_cast<int>(bottomRight.x+1); ++x) {
            Tile tile = tileInfo[mapData[y * mapWidth + x]];
            if (tile.textureIndex != 0) { // 0 is empty space
                tileSprite.setTextureRect(sf::IntRect({static_cast<int>((tile.textureIndex-1)*32),0},{32,32})); 
                tileSprite.setPosition({static_cast<float>(x * 32 * globals::scalingFactor),static_cast<float>(y * 32 * globals::scalingFactor)});
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
    std::ifstream file("assets/maps/" + name + ".game-map");

    if (!file.is_open()) {
        logging::ERROR("Failed to open map file: " + name);
        return;
    }

    float spawnPosX, spawnPosY;
    file >> spawnPosX >> spawnPosY;

    player.setPosition({spawnPosX, spawnPosY});


    file >> mapWidth >> mapHeight;
    mapData.resize(mapWidth * mapHeight);

    std::set<int> tileIds;

    int mult, tile;
    int index = 0; // position in mapData
    while (index < mapWidth * mapHeight) {
        file >> mult >> tile;
        tileIds.insert(tile);
        for (int n = 0; n < mult && index < mapWidth * mapHeight; n++) {
            mapData[index++] = tile;
        }
    }

    tileInfo.clear();
    int id,flags,layer;
    for(int i=0;i<tileIds.size();i++){
        file >> id >> flags >> layer;
        tileInfo[id] = {id,flags,layer};
    }

    logging::INFO("Loaded map:", name);
}
