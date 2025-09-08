#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    auto window = sf::RenderWindow(sf::VideoMode(desktopMode), "Survive IZV");
    
    Game game(window);
    game.run();
}
