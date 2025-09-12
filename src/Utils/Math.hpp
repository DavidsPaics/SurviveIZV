#pragma once
#include <SFML/System.hpp>
#include "Utils/globals.hpp"


inline float tilesToPixels(float tiles) {
    return (tiles * globals::tileSize * globals::scalingFactor);
}
inline sf::Vector2f tilesToPixelsV2F(sf::Vector2f tiles) {
    return {tilesToPixels(tiles.x), tilesToPixels(tiles.y)};
}


// --------------------------------
// Point inside Rectangle
// --------------------------------
bool rectPointCollision(const sf::FloatRect& rect, const sf::Vector2f& point) {
    return rect.contains(point);
}

// --------------------------------
// Rectangle vs Rectangle (AABB)
// --------------------------------
bool rectRectCollision(const sf::FloatRect& a, const sf::FloatRect& b) {
    return a.intersects(b);
}

// --------------------------------
// Rectangle vs Circle
// --------------------------------
bool rectCircleCollision(const sf::FloatRect& rect, const sf::Vector2f& circleCenter, float radius) {
    // Find closest point on rect to circle center
    float closestX = std::clamp(circleCenter.x, rect.left, rect.left + rect.width);
    float closestY = std::clamp(circleCenter.y, rect.top, rect.top + rect.height);

    float dx = circleCenter.x - closestX;
    float dy = circleCenter.y - closestY;

    return (dx * dx + dy * dy) <= (radius * radius);
}

// --------------------------------
// Circle vs Point
// --------------------------------
bool circlePointCollision(const sf::Vector2f& circleCenter, float radius, const sf::Vector2f& point) {
    float dx = point.x - circleCenter.x;
    float dy = point.y - circleCenter.y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

// --------------------------------
// Circle vs Circle
// --------------------------------
bool circleCircleCollision(const sf::Vector2f& c1, float r1, const sf::Vector2f& c2, float r2) {
    float dx = c2.x - c1.x;
    float dy = c2.y - c1.y;
    float radiusSum = r1 + r2;
    return (dx * dx + dy * dy) <= (radiusSum * radiusSum);
}