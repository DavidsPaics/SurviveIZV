#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Entities/Player.hpp"


class World {
public:
    World(const std::string map);

    void update(float deltaTime);
    void render(sf::RenderTarget& target);

    void handleEvent(sf::Event& event);

    void loadMap(const std::string& filename);

    Player& getPlayer() { return player; };

private:
    Player player;

    int mapWidth, mapHeight;
    std::vector<int> mapData;

    //rendering
    sf::Sprite tileSprite;

};