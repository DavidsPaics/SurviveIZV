#include <SFML/Graphics.hpp>
#include "Core/Game.hpp"

int main()
{

    //Implament main menu, restarting the WHOLE game here

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    auto window = sf::RenderWindow(sf::VideoMode(desktopMode), "Survive IZV");

    window.setVerticalSyncEnabled(true);
    
    Game game(window);
    game.run();
}
