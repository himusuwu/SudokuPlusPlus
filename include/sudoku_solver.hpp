#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER

#include <vector>
#include <cstddef>

std::vector<std::vector<int>> sudoku_solver(std::vector<std::vector<int>>& tmp_sudoku_table);
bool check_unique(std::vector<std::vector<int>> tmp_sudoku_table);

#endif