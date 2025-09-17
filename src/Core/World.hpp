#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "Entities/Player.hpp"
#include "Entities/Entity.hpp"
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

    void killEntity(int id){ //Remove from active entity vector, will ingore death animations, effects and such
        entities.erase(entities.begin()+id);
    };

    std::vector<int>& getMap() { return mapData; }
    sf::Vector2i getMapSize() { return {mapWidth, mapHeight}; }
    std::unordered_map<int, Tile>& getMapTileInfo() { return tileInfo; }

    Player& getPlayer() { return player; };

private:
    Player player;

    int mapWidth, mapHeight;
    std::vector<int> mapData; //basically in.txt
    std::string levelName="error";

    std::unordered_map<int, Tile> tileInfo;

    std::vector<std::unique_ptr<Entity>> entities;

    //rendering
    sf::Sprite tileSprite;

};