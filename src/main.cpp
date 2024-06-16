#include <SFML/Graphics.hpp>
#include "../include/Game.h"

int main()
{
    Game game({ 1920u, 1080u }, "CMake SFML Project");

    game.run();

    return 0;
}
