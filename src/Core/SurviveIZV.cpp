#include <SFML/Graphics.hpp>
#include "Core/Game.hpp"
#include "Ui/MainMenu.hpp"

int main()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    
    auto window = sf::RenderWindow(sf::VideoMode(desktopMode), "Survive IZV");
    
    window.setVerticalSyncEnabled(true);

    MainMenu menu(window);

    int action=0;
    while(window.isOpen()){
        action = menu.renderAndUpdate();
        if (action == 1){
            Game game(window);
            game.run();
        }
    }

}
