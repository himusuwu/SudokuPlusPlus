#ifndef SUDOKU_TABLE
#define SUDOKU_TABLE

#include <vector>

class Grid
{
  public:
    std::vector<std::vector<int>> sudoku_grid();

  private:
    std::vector<std::vector<int>> sudoku_table;
};

#endif
