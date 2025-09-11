#pragma once
#include <SFML/System.hpp>
#include "Utils/globals.hpp"


inline float tilesToPixels(float tiles) {
    return (tiles * globals::tileSize * globals::scalingFactor);
}
inline sf::Vector2f tilesToPixelsV2F(sf::Vector2f tiles) {
    return {tilesToPixels(tiles.x), tilesToPixels(tiles.y)};
}