#include "sudoku_solver.hpp"

bool Solver::is_valid(std::vector<std::vector<int>>& board, size_t row, size_t col, int possible_digit)
{
    for (size_t i = 0; i < 9; i++)
    {
        if (board[row][i] == possible_digit)
        {
            return false;
        }

        if (board[i][col] == possible_digit)
        {
            return false;
        }
    }

    const size_t startRow = (row / 3) * 3;
    const size_t startCol = (col / 3) * 3;

    for (size_t blockRow = 0; blockRow < 3; blockRow++)
    {
        for (size_t blockCol = 0; blockCol < 3; blockCol++)
        {
            size_t currentRow = startRow + blockRow;
            size_t currentCol = startCol + blockCol;

            if (board[currentRow][currentCol] == possible_digit)
            {
                return false;
            }
        }
    }

    return true;
}

bool Solver::solve(std::vector<std::vector<int>>& tmp_sudoku_table)
{
    for (size_t row = 0; row < tmp_sudoku_table.size(); row++)
    {
        for (size_t col = 0; col < tmp_sudoku_table[row].size(); col++)
        {
            if (tmp_sudoku_table[row][col] == 0)
            {
                for (size_t possible_digit = 1; possible_digit <= 9; possible_digit++)
                {
                    if (is_valid(tmp_sudoku_table, row, col, possible_digit))
                    {
                        tmp_sudoku_table[row][col] = possible_digit;

                        if (solve(tmp_sudoku_table))
                        {
                            return true;
                        }

                        tmp_sudoku_table[row][col] = 0;
                    }
                }

                return false;
            }
        }
    }

    return true;
}

void Solver::can_be_solved_and_is_unique(std::vector<std::vector<int>>& tmp_sudoku_table, size_t& solutions)
{
    for (size_t row = 0; row < tmp_sudoku_table.size(); row++)
    {
        for (size_t col = 0; col < tmp_sudoku_table[row].size(); col++)
        {
            if (tmp_sudoku_table[row][col] == 0)
            {
                for (size_t possible_digit = 1; possible_digit <= 9; possible_digit++)
                {
                    if (is_valid(tmp_sudoku_table, row, col, possible_digit))
                    {
                        tmp_sudoku_table[row][col] = possible_digit;

                        can_be_solved_and_is_unique(tmp_sudoku_table, solutions);

                        if (solutions > 1)
                        {
                            tmp_sudoku_table[row][col] = 0;
                            return;
                        }

                        tmp_sudoku_table[row][col] = 0;
                    }
                }

                return;
            }
        }
    }

    solutions++;
}

bool Solver::check_unique(std::vector<std::vector<int>> tmp_sudoku_table)
{
    solutions = 0;

    can_be_solved_and_is_unique(tmp_sudoku_table, solutions);

    return solutions == 1;
}

std::vector<std::vector<int>> Solver::sudoku_solver(std::vector<std::vector<int>>& tmp_sudoku_table)
{
    solve(tmp_sudoku_table);

    return tmp_sudoku_table;
}
