#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(float windowWidth, float windowHeight);

    void setTarget(const sf::Vector2f& target);
    void setCenter(const sf::Vector2f& target);
    void setZoom(float zoom); // absolute zoom
    void update(float deltaTime);
    const sf::View& getView() const;

private:
    sf::View view;
    sf::Vector2f targetPos;
    sf::Vector2f smoothPos;
    float smoothing;

    sf::Vector2f originalSize; // store original view size
    float currentZoom = 1.f;   // store current absolute zoom
};