#include <SFML/Graphics.hpp>
#include "Core/Game.hpp"

int main()
{

    //Implament main menu, restarting the WHOLE game here

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    auto window = sf::RenderWindow(sf::VideoMode(desktopMode), "Survive IZV");
    
    Game game(window);
    game.run();
}
