#pragma once
#include <utility>
#include <string>
#include <SFML/Graphics.hpp>
#include "Utils/globals.hpp"

inline float tilesToPixels(float tiles) {
    return (tiles * globals::tileSize * globals::scalingFactor);
}
inline sf::Vector2f tilesToPixelsV2F(sf::Vector2f tiles) {
    return {tilesToPixels(tiles.x), tilesToPixels(tiles.y)};
}

inline float pixelsToTiles(float pixels) {
    return (pixels / globals::scaledTileSize);
}
inline sf::Vector2f pixelsToTilesV2F(sf::Vector2f pixels) {
    return {pixelsToTiles(pixels.x), pixelsToTiles(pixels.y)};
}
inline sf::FloatRect pixelsToTilesFloatRect(sf::FloatRect pixels) {
    return sf::FloatRect({pixelsToTiles(pixels.position.x), pixelsToTiles(pixels.position.y)},{pixelsToTiles(pixels.size.x), pixelsToTiles(pixels.size.y)});
}


// --------------------------------
// Point inside Rectangle
// --------------------------------
inline bool rectPointCollision(const sf::FloatRect& rect, const sf::Vector2f& point) {
    return rect.contains(point);
}

// --------------------------------
// Rectangle vs Rectangle (AABB)
// --------------------------------
inline bool rectRectCollision(const sf::FloatRect& a, const sf::FloatRect& b) {
    return a.findIntersection(b).has_value();
}

// --------------------------------
// Circle vs Point
// --------------------------------
inline bool circlePointCollision(const sf::Vector2f& circleCenter, float radius, const sf::Vector2f& point) {
    float dx = point.x - circleCenter.x;
    float dy = point.y - circleCenter.y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

// --------------------------------
// Circle vs Circle
// --------------------------------
inline bool circleCircleCollision(const sf::Vector2f& c1, float r1, const sf::Vector2f& c2, float r2) {
    float dx = c2.x - c1.x;
    float dy = c2.y - c1.y;
    float radiusSum = r1 + r2;
    return (dx * dx + dy * dy) <= (radiusSum * radiusSum);
}

// --------------------------------
// Circle vs Rectangle (AABB)
// --------------------------------
inline bool circleRectCollision(const sf::FloatRect& rect, const sf::Vector2f& circleCenter, float radius) {
    // Clamp circle center to rectangle bounds
    float closestX = std::clamp(circleCenter.x, rect.position.x, rect.position.x + rect.size.x);
    float closestY = std::clamp(circleCenter.y, rect.position.y, rect.position.y + rect.size.y);

    // Distance from circle center to closest point
    float dx = circleCenter.x - closestX;
    float dy = circleCenter.y - closestY;

    return (dx * dx + dy * dy) <= (radius * radius);
}

bool isWithinRange(float x,float y, float range);
int coordsToMapIndex(int x, int y);
sf::Vector2f mapIndexToCoords(int mapIndex);


inline std::vector<std::vector<std::pair<int, double>>> mapGraph; //pair<int,int> is pair<vertex, weight> for dijkstra
void generateGraphFromMap();
void dijkstra(int s, std::vector<int> & distance, std::vector<int> & path);
sf::Vector2f pathfind(sf::Vector2f startPos,sf::Vector2f endPos);

