#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({320u, 180u}), "CMake SFML Project", sf::Style::Default);
    window.setFramerateLimit(60);
    sf::CircleShape shape(32.f);
    // set the shape color to green
    shape.setFillColor(sf::Color(100, 250, 50));

    while (window.isOpen())
    {

        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        window.clear();
        
        window.draw(shape);

        window.display();
    }
}
