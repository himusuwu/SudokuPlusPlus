#include <iostream>

#include <raylib.h>

#include "shuffle_board.hpp"
#include "sudoku_grid.hpp"
#include "sudoku_generator.hpp"
#include "gui/game.hpp"

int main()
{   
    srand( time( nullptr ) );

    size_t difficulty{};

    size_t menu_choice{};

    /*
    std::cout << "1. Generate Sudoku" << std::endl
        << "2. Solve Sudoku from file" << std::endl;
    std::cin >> menu_choice;

    std::cout << "Choose difficulty (1, 2, 3, 4): " << std::endl;
    std::cin >> difficulty;

    std::vector<std::vector<int>> sudoku_table = sudoku_grid();

    shuffle_board(sudoku_table);

    sudoku_table = sudoku_generator(sudoku_table, difficulty 1);
    */

    const int screenWidth = 600;
    const int screenHeight = 800;

    Game game(screenWidth, screenHeight);
    game.run();

    //Tests
    //std::cout << random_1 << " " << random_2 << std::endl << std::endl;

    /*for(size_t i = 0; i < sudoku_table.size(); i++)
    {
        if(i % 3 == 0)
        {
            std::cout << "+-----+-----+-----+" << std::endl;
        }

        for(size_t j = 0; j < sudoku_table[i].size(); j++)
        {
            if(sudoku_table[i][j] == 0)
            {
                std::cout << "|" << " ";
            }
            else
            {
                std::cout << "|" << sudoku_table[i][j];
            }            
        }

        std::cout << "|" << std::endl;
    }

    std::cout << "+-----+-----+-----+" << std::endl;

    std::cout << std::endl;

    
    for(const auto& x : field_list)
    {
        std::cout << x.col << ", " << x.row << std::endl;
    }

    std::cout << std::endl;
    */
    return 0;
}