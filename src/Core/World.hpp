#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Entities/Player.hpp"
#include "Game/Camera.hpp"

struct Tile{
    int textureIndex;
    int flags;
    int layer;
};

class World {
public:
    World(const std::string map);

    void update(float deltaTime);
    void render(sf::RenderTarget& target, Camera& camera);

    void handleEvent(sf::Event& event);

    void loadMap(const std::string& filename);

    std::vector<int>& getMap() { return mapData; }
    sf::Vector2i getMapSize() { return {mapWidth, mapHeight}; }
    std::unordered_map<int, Tile>& getMapTileInfo() { return tileInfo; }

    Player& getPlayer() { return player; };

private:
    Player player;

    int mapWidth, mapHeight;
    std::vector<int> mapData; //basically in.txt

    std::unordered_map<int, Tile> tileInfo;

    //rendering
    sf::Sprite tileSprite;

};