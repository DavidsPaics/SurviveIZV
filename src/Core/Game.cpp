#include <SFML/Graphics.hpp>
#include "Utils/logging.hpp"
#include "Game.hpp"
#include "Utils/globals.hpp"
#include "Utils/TextureManager.hpp"

Game::Game(sf::RenderWindow &window) : window(window), renderTexture(globals::renderResolution), renderSprite(renderTexture.getTexture())
{
    // Set up the sprite that will draw the renderTexture onto the window
    renderSprite.setTexture(renderTexture.getTexture());

    handleResize();
}

void Game::run()
{
    logging::INFO("Game started");

    auto testCoords = sf::Vector2f({100,100});

    sf::Font funFont("assets/fonts/COMIC.ttf");

    clock.restart();

    sf::Clock deltaClock;
    float deltaTime = 0.0f;

    sf::Clock fpsUpdateClock;
    int frameCount = 0;

    while (window.isOpen())
    {
        deltaTime = deltaClock.restart().asSeconds();

        handleEvents();
        
        frameCount++;
        if (fpsUpdateClock.getElapsedTime().asSeconds() > 1) {
            std::cout << frameCount << " FPS\n";
            frameCount = 0;
            fpsUpdateClock.restart();
        }
        world.update(deltaTime);
        
        // Render to off-screen render texture
        renderTexture.clear(sf::Color::Blue);


        world.render(renderTexture);


        renderTexture.display();

        ////////////////////////////////////////////

        // Render to the actual window
        // window.setView(window.getDefaultView()); //FIXME: remove for camera,hack to resize
        window.clear(sf::Color::Black);
        window.draw(renderSprite);
        window.display();
    }
}


//FIXME: THIS IS COMPLATELY BROKEN, I AM LOSING MY MIND, IT WORKS ON FIRST RUN BUT NOT ON RESIZE
void Game::handleResize()
{
    // Don't reassign the texture here — set it once in the constructor.
    // Reset only transform state
    renderSprite.setScale({1.f, 1.f});
    renderSprite.setOrigin({0.f, 0.f});
    renderSprite.setPosition({0.f, 0.f});

    const auto win = window.getSize();
    const auto tex = renderTexture.getSize();

    // Debug print once per resize (helpful)
    std::cout << "RESIZE win=" << win.x << "x" << win.y
              << " tex=" << tex.x << "x" << tex.y << "\n";

    const float scaleX = static_cast<float>(win.x) / static_cast<float>(tex.x);
    const float scaleY = static_cast<float>(win.y) / static_cast<float>(tex.y);
    const float scale  = std::min(scaleX, scaleY);

    renderSprite.setScale({scale, scale});

    // origin in local tex coordinates (untransformed)
    renderSprite.setOrigin({static_cast<float>(tex.x) * 0.5f,
                            static_cast<float>(tex.y) * 0.5f});

    renderSprite.setPosition({static_cast<float>(win.x) * 0.5f,
                              static_cast<float>(win.y) * 0.5f});
}



void Game::handleEvents()
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        //shit
        // if (event->is<sf::Event::Resized>())
        // {
        //     handleResize();
        // }
    }
}