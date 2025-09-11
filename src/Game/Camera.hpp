#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(float windowWidth, float windowHeight);
    void setTarget(const sf::Vector2f& target);

    void setZoom(float factor);

    void update(float deltaTime);

    const sf::View& getView() const;

private:
    sf::View view;
    sf::Vector2f targetPos;    // where the camera should move towards
    sf::Vector2f smoothPos;    // current smoothed position

    float smoothing;           // how fast the camera catches up
};
