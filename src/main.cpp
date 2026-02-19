#include <iostream>

#include <raylib.h>

#include "shuffle_board.hpp"
#include "sudoku_grid.hpp"
#include "sudoku_generator.hpp"
#include "gui/game.hpp"

int main()
{   
    srand( time( nullptr ) );

    const int screenWidth = 600;
    const int screenHeight = 800;

    Game game(screenWidth, screenHeight);
    game.run();

    //Tests

    return 0;
}