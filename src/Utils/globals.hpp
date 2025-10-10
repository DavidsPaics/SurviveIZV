                                         #pragma once
                                      #include <memory>
                                 #include <SFML/Graphics.hpp>


                                         class World;
                                     namespace globals {
                  inline constexpr auto scalingFactor = 4; // 2 - 8 is good
    inline constexpr auto renderResolution = sf::Vector2u({640*scalingFactor,360*scalingFactor});
                             inline constexpr auto tileSize = 32;
               inline constexpr auto scaledTileSize = tileSize * scalingFactor;
                            inline World* currentWorld = nullptr;
                                              }