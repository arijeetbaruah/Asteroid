#include <SFML/Graphics.hpp>
#include "../build/GameStateMachine.h"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    sf::Clock clock;
    GameStateMachine game;
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
        game.Update(elapsed);

        window.clear();
        window.display();
        game.Render(window);
    }
}
