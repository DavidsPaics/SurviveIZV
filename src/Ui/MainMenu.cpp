                               #include "Ui/MainMenu.hpp"
                           #include "Utils/TextureManager.hpp"
                                    #include <cmath>

                      MainMenu::MainMenu(sf::RenderWindow& window)
                                    : window(window)
      , backdrop(TextureManager::getInstance().getTexture("ui/mainMenu/backdrop"))
      , titleSprite(TextureManager::getInstance().getTexture("ui/mainMenu/title"))
   , startButton(TextureManager::getInstance().getTexture("ui/mainMenu/startButton"))
, settingsButton(TextureManager::getInstance().getTexture("ui/mainMenu/settingsButton"))
                                            {
                                    // Center origins
                         auto centerOrigin = [](sf::Sprite& s) {
                              auto b = s.getLocalBounds();
                    s.setOrigin({ b.size.x / 2.f, b.size.y / 2.f });
                                           };
                                 centerOrigin(backdrop);
                               centerOrigin(titleSprite);
                               centerOrigin(startButton);
                              centerOrigin(settingsButton);

                           lastWindowSize = window.getSize();
                                    updateScaling();

                                  // Reset hover clock
                                  hoverClock.restart();
                                            }

                            int MainMenu::renderAndUpdate() {
           while (const std::optional<sf::Event> event = window.pollEvent()) {
                           if (event->is<sf::Event::Closed>())
                                     window.close();
                                            }

                                  if (!areSettingsOpen)
                                   doTheTitleScreen();

                         // --- Check for Start button click ---
                     auto mousePos = sf::Mouse::getPosition(window);
                    auto startBounds = startButton.getGlobalBounds();

                bool overStart = (mousePos.x >= startBounds.position.x &&
                      mousePos.x <= startBounds.position.x + startBounds.size.x &&
                         mousePos.y >= startBounds.position.y &&
                      mousePos.y <= startBounds.position.y + startBounds.size.y);

          if (overStart && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                          return 1;            // run game once

                                        return 0;
                                            }

                           void MainMenu::doTheTitleScreen() {
                                 window.clear({0,0,64});

                        if (window.getSize() != lastWindowSize) {
                           lastWindowSize = window.getSize();
                                    updateScaling();
                                            }

                                 window.draw(backdrop);

                               // Title rotation animation
               float t = titleRotationClock.getElapsedTime().asSeconds();
                    float degrees = 5.f * std::sin(t * 0.5f);  // ±5°
                     titleSprite.setRotation(sf::degrees(degrees));

                                window.draw(titleSprite);

                        // Smooth transitions require delta time
                      float dt = hoverClock.restart().asSeconds();
                                    drawButtons(dt);

                                    window.display();
                                            }

                            void MainMenu::updateScaling() {
                            auto winSize = window.getSize();
                     auto texSize = backdrop.getTexture().getSize();

                float scaleX = static_cast<float>(winSize.x) / texSize.x;
                float scaleY = static_cast<float>(winSize.y) / texSize.y;
                         float scale = std::max(scaleX, scaleY);
                          backdrop.setScale({ scale, scale });
               backdrop.setPosition({ winSize.x / 2.f, winSize.y / 2.f });

                                 // Apply initial scales
              titleSprite.setScale({ titleScaleFactor, titleScaleFactor });
             startButton.setScale({ buttonScaleFactor, buttonScaleFactor });
           settingsButton.setScale({ buttonScaleFactor, buttonScaleFactor });

                                    // Position title
             titleSprite.setPosition({ winSize.x / 2.f, winSize.y * 0.2f });

                                 // Reset current scales
                        startCurrentScale    = buttonScaleFactor;
                        settingsCurrentScale = buttonScaleFactor;
                                            }

                         void MainMenu::drawButtons(float dt) {
                            auto winSize = window.getSize();
                                  float spacing = 20.f;

             startButton.setPosition({ winSize.x / 2.f, winSize.y * 0.5f });
                              settingsButton.setPosition({
                                    winSize.x / 2.f,
        startButton.getPosition().y + startButton.getGlobalBounds().size.y + spacing
                                           });

                     auto mousePos = sf::Mouse::getPosition(window);

            auto smoothHover = [&](sf::Sprite& button, float& currentScale) {
                         auto bounds = button.getGlobalBounds();
                         float targetScale = buttonScaleFactor;

                   bool hovered = (mousePos.x >= bounds.position.x &&
                        mousePos.x <= bounds.position.x + bounds.size.x &&
                           mousePos.y >= bounds.position.y &&
                        mousePos.y <= bounds.position.y + bounds.size.y);

                                      if (hovered)
             targetScale = buttonScaleFactor * 1.1f; // enlarge 10% on hover

                            // Smoothly approach target scale
                        float speed = 12.f; // larger = snappier
        currentScale += (targetScale - currentScale) * std::min(speed * dt, 1.f);

                    button.setScale({ currentScale, currentScale });
                                           };

                      smoothHover(startButton, startCurrentScale);
                   smoothHover(settingsButton, settingsCurrentScale);

                                window.draw(startButton);
                              window.draw(settingsButton);
                                            }
