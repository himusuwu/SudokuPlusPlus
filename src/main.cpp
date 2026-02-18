#include <iostream>

#include "shuffle_board.hpp"
#include "sudoku_grid.hpp"
#include "sudoku_generator.hpp"

int main()
{   
    srand( time( nullptr ) );

    std::vector<std::vector<int>> sudoku_table = sudoku_grid();

    shuffle_board(sudoku_table);

    sudoku_generator(sudoku_table);

    //Tests
    //std::cout << random_1 << " " << random_2 << std::endl << std::endl;

    for(size_t i = 0; i < sudoku_table.size(); i++)
    {
        for(size_t j = 0; j < sudoku_table[i].size(); j++)
        {
            std::cout << sudoku_table[i][j];
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    /*
    for(const auto& x : field_list)
    {
        std::cout << x.col << ", " << x.row << std::endl;
    }

    std::cout << std::endl;
    */

    return 0;
}