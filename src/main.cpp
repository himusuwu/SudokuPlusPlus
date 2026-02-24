#include "gui/game.hpp"

#include <raylib.h>

int main()
{
    const int screenWidth = 600;
    const int screenHeight = 1000;

    Game game(screenWidth, screenHeight);
    game.run();

    // Tests

    return 0;
}
