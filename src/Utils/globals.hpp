#pragma once
#include <memory>
#include <SFML/Graphics.hpp>


class World;
namespace globals {
    inline float globalSpeedMultiplier = 1;
    inline bool isVsyncEnabled=1;
    inline constexpr int framerateLimit = 480;

    inline constexpr int scalingFactor = 4; // 2 - 8 is good
    inline constexpr auto renderResolution = sf::Vector2u({640*scalingFactor,360*scalingFactor});
    inline constexpr int tileSize = 32;
    inline constexpr int scaledTileSize = tileSize * scalingFactor;
    inline World* currentWorld = nullptr;
}