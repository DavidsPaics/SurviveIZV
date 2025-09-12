#pragma once
#include <SFML/Graphics.hpp>
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