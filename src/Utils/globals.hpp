#pragma once
#include <SFML/Graphics.hpp>

namespace globals {
    inline constexpr auto scalingFactor = 4; // 2 - 8 is good
    inline constexpr auto renderResolution = sf::Vector2u({640*scalingFactor,360*scalingFactor});

    inline constexpr auto tileSize = 32;
    inline constexpr auto scaledTileSize = tileSize * scalingFactor;
}


struct Tile{
    unsigned int textureIndex;
    unsigned int layer;
};


inline std::unordered_map<int,Tile> tileInfo = {
    {-1,{1,1}}, //error tile
    {1,{4,1}}, //debug tile
    {2,{2,0}}, //stone tile
    {3,{3,1}}, //brick tile
    {4,{2,0}} //spawnpoint tile
}; 