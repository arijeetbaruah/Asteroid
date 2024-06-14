#include <SFML/Graphics.hpp>
#include "../include/Game.h"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    sf::Clock clock;
    Game game;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        game.update(elapsed);

        window.clear();
        game.render(window);
        window.display();
    }
}
