#include "sudoku_generator.hpp"

bool is_valid(std::vector<std::vector<int>>& board, size_t row, size_t col, int possible_digit)
{
    for(size_t i = 0; i < 9; i++)
    {
        if(board[row][i] == possible_digit)
        {
            return false;
        }

        if(board[i][col] == possible_digit)
        {
            return false;
        }
    }

    size_t startRow = (row / 3) * 3;
    size_t startCol = (col / 3) * 3;

    for(size_t blockRow = 0; blockRow < 3; blockRow++)
    {
        for(size_t blockCol = 0; blockCol < 3; blockCol++)
        {
            size_t currentRow = startRow + blockRow;
            size_t currentCol = startCol + blockCol;

            if(board[currentRow][currentCol] == possible_digit)
            {
                return false;
            }
        }
    }

    return true;
}

bool can_be_solved(std::vector<std::vector<int>>& tmp_sudoku_table)
{
    for(size_t row = 0; row < tmp_sudoku_table.size(); row++)
    {
        for(size_t col = 0; col < tmp_sudoku_table[row].size(); col++)
        {
            if(tmp_sudoku_table[row][col] == 0)
            {
                for(size_t possible_digit = 1; possible_digit <= 9; possible_digit++)
                {
                    if(is_valid(tmp_sudoku_table, row, col, possible_digit))
                    {
                        tmp_sudoku_table[row][col] = possible_digit;

                        if(can_be_solved(tmp_sudoku_table))
                        {
                            return true;
                        }

                        tmp_sudoku_table[row][col] = 0;
                    }
                }
            }

            return false;
        }
    }

    return true;
}

std::vector<std::vector<int>> sudoku_solver(std::vector<std::vector<int>>& tmp_sudoku_table)
{
    can_be_solved(tmp_sudoku_table);

    return tmp_sudoku_table;
}