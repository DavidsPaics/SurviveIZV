#include <SFML/Graphics.hpp>
#include "Utils/logging.hpp"
#include "Core/Game.hpp"
#include "Utils/globals.hpp"
#include "Ui/Camera.hpp"
#include "Utils/TextureManager.hpp"

Game::Game(sf::RenderWindow &window) : window(window), world("IZV-main"), renderTexture(globals::renderResolution), renderSprite(renderTexture.getTexture())
{
    // Set up the sprite that will draw the renderTexture onto the window
    renderSprite.setTexture(renderTexture.getTexture());

    handleResize();
}

void Game::run()
{
    logging::INFO("Game started, resolution: ", globals::renderResolution.x, "x", globals::renderResolution.y, " (", globals::scalingFactor, "x scale)");

    sf::Clock deltaClock, fpsUpdateClock;
    float deltaTime = 0.0f;
    
    int frameCount = 0;
    
    Camera camera(renderTexture.getSize().x, renderTexture.getSize().y);
    camera.setCenter(world.getPlayer().getPosition());


    while (window.isOpen())
    {
        deltaTime = deltaClock.restart().asSeconds()*globals::globalSpeedMultiplier;
        
        frameCount++;
        if (fpsUpdateClock.getElapsedTime().asSeconds() > 1) {
            std::cout << frameCount << " FPS\n";
            frameCount = 0;
            fpsUpdateClock.restart();
        }
        
        handleEvents();
        world.update(deltaTime);


        camera.setTarget(world.getPlayer().getPosition());
        camera.update(deltaTime);


        renderTexture.setView(camera.getView());
        
        // Render to off-screen render texture
        renderTexture.clear(sf::Color::Black);

        world.render(renderTexture, camera);

        renderTexture.display();

        ////////////////////////////////////////////

        // Render to the actual window
        window.clear(sf::Color::Black);
        window.draw(renderSprite);
        window.display();
    }
}


//FIXME: THIS IS COMPLETELY BROKEN, I AM LOSING MY MIND, IT WORKS ON FIRST RUN BUT NOT ON RESIZE
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
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::F3)
                logging::DEBUG("Player position:", world.getPlayer().getPosition().x, world.getPlayer().getPosition().y);
            else if (keyPressed->scancode == sf::Keyboard::Scancode::F4){
                if (globals::globalSpeedMultiplier==1)
                globals::globalSpeedMultiplier = 0.5;
                else
                globals::globalSpeedMultiplier=1;
            }
        }
    }
}