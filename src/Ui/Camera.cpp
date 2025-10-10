                     #include "Camera.hpp"
                   #include "Utils/math.hpp"
                        #include <cmath>

     Camera::Camera(float windowWidth, float windowHeight)
    : view(sf::FloatRect({0, 0}, {windowWidth, windowHeight})),
                      targetPos(0.f, 0.f),
                      smoothPos(0.f, 0.f),
                        smoothing(10.f),
            originalSize(windowWidth, windowHeight)
                               {
                               }

      void Camera::setTarget(const sf::Vector2f& target) {
             targetPos = tilesToPixelsV2F(target);
                               }

      void Camera::setCenter(const sf::Vector2f& target) {
             targetPos = tilesToPixelsV2F(target);
           view.setCenter(tilesToPixelsV2F(target));
             smoothPos = tilesToPixelsV2F(target);
                               }

               void Camera::setZoom(float zoom) {
         // Calculate relative factor from current zoom
               float factor = zoom / currentZoom;
                       view.zoom(factor);
         currentZoom = zoom; // store new absolute zoom
                               }

             void Camera::update(float deltaTime) {
    smoothPos += (targetPos - smoothPos) * (smoothing * deltaTime);
    
                     sf::Vector2f rounded(
                    std::round(smoothPos.x),
                    std::round(smoothPos.y)
                               );
                    view.setCenter(rounded);
                               }

           const sf::View& Camera::getView() const {
                          return view;
                               }