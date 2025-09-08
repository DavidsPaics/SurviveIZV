#include <SFML/Graphics.hpp>
#include "logging.hpp"
#include "Game.hpp"

Game::Game(sf::RenderWindow &window) : window(window), renderTexture({640,360}), renderSprite(renderTexture.getTexture())
{
    // Set up the sprite that will draw the renderTexture onto the window
    renderSprite.setTexture(renderTexture.getTexture());

    // Calculate scale factor to fit the window
    float scaleX = static_cast<float>(window.getSize().x) / renderTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / renderTexture.getSize().y;
    renderSprite.setScale({scaleX, scaleY});
}

void Game::run()
{
    logging::INFO("Game started");

    auto testCoords = sf::Vector2f({100,100});

    window.setFramerateLimit(60);

    sf::CircleShape shape(32.f);
    shape.setFillColor(sf::Color(100, 250, 50));

    clock.restart();

    sf::Clock deltaClock;
    float deltaTime = 0.0f;

    while (window.isOpen())
    {
        handleEvents();

        // FIXME: REMOVE SOON
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            testCoords.x += 100.f * deltaTime;
        }
        shape.setPosition(testCoords);
        //////

        deltaTime = deltaClock.restart().asSeconds();
        // world.update(deltaTime);

        // Render to off-screen render texture
        renderTexture.clear(sf::Color::Black);
        renderTexture.draw(shape);
        renderTexture.display();

        // Render to the actual window
        window.clear(sf::Color::Black);
        window.draw(renderSprite);
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
    }
}