                    #pragma once
            #include <SFML/Graphics.hpp>

                  class MainMenu {
                      public:
        MainMenu(sf::RenderWindow& window);
               int renderAndUpdate();

                      private:
             sf::RenderWindow& window;
           bool areSettingsOpen = false;

                sf::Sprite backdrop;
              sf::Sprite titleSprite;
              sf::Sprite startButton;
             sf::Sprite settingsButton;

    sf::Clock hoverClock;             // for delta time
           sf::Clock titleRotationClock;

           float buttonScaleFactor = 4.f;
           float titleScaleFactor  = 5.f;

            // Per-button smooth scales
    float startCurrentScale    = buttonScaleFactor;
    float settingsCurrentScale = buttonScaleFactor;

            sf::Vector2u lastWindowSize;

              void doTheTitleScreen();
               void updateScaling();
            void drawButtons(float dt);
                         };
