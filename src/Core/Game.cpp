#include <SFML/Graphics.hpp>
#include "Utils/logging.hpp"
#include "Game.hpp"
#include "Utils/globals.hpp"
#include "Utils/TextureManager.hpp"

Game::Game(sf::RenderWindow &window) : window(window), renderTexture(globals::renderResolution), renderSprite(renderTexture.getTexture())
{
    // Set up the sprite that will draw the renderTexture onto the window
    renderSprite.setTexture(renderTexture.getTexture());

    // Calculate scale factor to fit the window
    float scaleX = static_cast<float>(window.getSize().x) / renderTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / renderTexture.getSize().y;
    renderSprite.setScale({std::min(scaleX, scaleY), std::min(scaleX, scaleY)});

    sf::FloatRect bounds = renderSprite.getLocalBounds();
    renderSprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    // Position in the center of the window
    renderSprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
}
void Game::run()
{
    logging::INFO("Game started");

    auto testCoords = sf::Vector2f({100,100});

    sf::Font funFont("assets/fonts/COMIC.ttf");
    
    // FPS Text
    sf::Text fpsText(funFont, "fps:");
    fpsText.setStyle(sf::Text::Bold);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setPosition({50,10});

    // window.setFramerateLimit(60);

    sf::Sprite testSprite(TextureManager::getInstance().getTexture("test"));

    sf::CircleShape shape(32.f);
    shape.setFillColor(sf::Color(100, 250, 50));

    clock.restart();

    sf::Clock deltaClock;
    float deltaTime = 0.0f;

    sf::Clock fpsClock;

    while (window.isOpen())
    {
        handleEvents();

        // FIX: REMOVE SOON
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            testCoords.x += 100.f * deltaTime;
        }
        testSprite.setPosition(testCoords);
        //////

        deltaTime = deltaClock.restart().asSeconds();
        // world.update(deltaTime);

        // Render to off-screen render texture
        renderTexture.clear(sf::Color::Blue);
        renderTexture.draw(testSprite);
        renderTexture.display();

        // Render to the actual window
        window.clear(sf::Color::Black);
        window.draw(renderSprite);

        if (debugEnabled)
        {
            if (fpsClock.getElapsedTime().asMilliseconds() > 500){
                std::ostringstream ss;
                ss << std::fixed << std::setprecision(0) << (1.0f/deltaTime) << " FPS";
                fpsText.setString(ss.str());
                fpsClock.restart();
            }
            window.draw(fpsText);
        }


        window.display();
    }
}



void Game::handleEvents()
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::F3)
            {
                debugEnabled = !debugEnabled;
            }
        }

    }
}