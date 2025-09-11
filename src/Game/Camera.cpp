#include "Camera.hpp"
#include "Utils/Math.hpp"

Camera::Camera(float windowWidth, float windowHeight)
    : view(sf::FloatRect({0, 0}, {windowWidth, windowHeight})),
      targetPos(0.f, 0.f),
      smoothPos(0.f, 0.f),
      smoothing(10.f) // higher = snappier, lower = smoother
{
}

void Camera::setTarget(const sf::Vector2f& target) {
    targetPos = tilesToPixelsV2F(target);
}

void Camera::setZoom(float factor) {
    view.zoom(factor);
}

void Camera::update(float deltaTime) {
    // Smooth interpolation towards target
    smoothPos += (targetPos - smoothPos) * (smoothing * deltaTime);

    view.setCenter(smoothPos);
}

const sf::View& Camera::getView() const {
    return view;
}
