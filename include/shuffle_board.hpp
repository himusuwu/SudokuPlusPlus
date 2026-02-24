#ifndef SHUFFLE_BOARD
#define SHUFFLE_BOARD

#include <vector>

class Shuffler
{
  public:
    std::vector<std::vector<int>> shuffle_board(std::vector<std::vector<int>>& sudoku_table);

  private:
    size_t random_1;
    size_t random_2;

    size_t random_row_1;
    size_t random_row_2;

    size_t random_col_1;
    size_t random_col_2;

    size_t possibility;
};

#endif
