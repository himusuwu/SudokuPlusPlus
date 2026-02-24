#include <iostream>

#include <raylib.h>

#include "shuffle_board.hpp"
#include "sudoku_grid.hpp"
#include "sudoku_generator.hpp"
#include "gui/game.hpp"

int main()
{
    const int screenWidth = 600;
    const int screenHeight = 1000;

    Game game(screenWidth, screenHeight);
    game.run();

    //Tests

    return 0;
}