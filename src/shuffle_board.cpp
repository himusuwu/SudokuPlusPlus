#include "shuffle_board.hpp"
#include "random_gen.hpp"

std::vector<std::vector<int>> Shuffler::shuffle_board(std::vector<std::vector<int>>& sudoku_table)
{
    RandomGen random;

    random_1 = random.random_int(1, 8);
    random_2 = random.random_int(1, 8);

    if(random_1 == random_2)
    {
        if(random_1 == 1)
        {
            random_1 += 1;
        }
        else
        {
            random_1 -= 1;
        }
    }

    for(size_t i = 0; i < sudoku_table.size(); i++)
    {
        for(size_t j = 0; j < sudoku_table[i].size(); j++)
        {
            if(sudoku_table[i][j] == random_1)
            {
                sudoku_table[i][j] = random_2;
                continue;
            }

            if(sudoku_table[i][j] == random_2)
            {
                sudoku_table[i][j] = random_1;
                continue;
            }
        }
    }

    for(size_t block = 0; block < 3; block++)
    {
        random_row_1 = block * 3 + random.random_int(0, 2);
        random_row_2 = block * 3 + random.random_int(0, 2);

        sudoku_table[random_row_1].swap(sudoku_table[random_row_2]);
    }

    for(size_t block = 0; block < 3; block++)
    {
        random_col_1 = block * 3 + random.random_int(0, 2);
        random_col_2 = block * 3 + random.random_int(0, 2);

        for(size_t row = 0; row < sudoku_table.size(); row++)
        {
            std::swap(sudoku_table[row][random_col_1], sudoku_table[row][random_col_2]);
        }
    }

    possibility = std::rand() % 2;

    if(possibility == 1)
    {
        std::vector<std::vector<int>> tmp_sudoku(sudoku_table[0].size(), std::vector<int>(sudoku_table.size()));

        for(size_t row = 0; row < sudoku_table.size(); row++)
        {
            for(size_t col = 0; col < sudoku_table[row].size(); col++)
            {
                tmp_sudoku[col][row] = sudoku_table[row][col];
            }
        }

        sudoku_table = tmp_sudoku;
    }

    return sudoku_table;
}