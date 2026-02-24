#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER

#include <cstddef>
#include <vector>

class Solver
{
  public:
    [[nodiscard]] std::vector<std::vector<int>> sudoku_solver(std::vector<std::vector<int>>& tmp_sudoku_table);

    [[nodiscard]] bool check_unique(std::vector<std::vector<int>> tmp_sudoku_table);

  private:
    [[nodiscard]] bool is_valid(std::vector<std::vector<int>>& board, size_t row, size_t col, int possible_digit);

    bool solve(std::vector<std::vector<int>>& tmp_sudoku_table);

    void can_be_solved_and_is_unique(std::vector<std::vector<int>>& tmp_sudoku_table, size_t& solutions);

    size_t solutions{};
};

#endif
