#ifndef SUDOKU_GENERATOR
#define SUDOKU_GENERATOR

#include "Config.hpp"

#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>

class Generate
{
  public:
    std::vector<std::vector<int>> sudoku_generator(std::vector<std::vector<int>>& sudoku_table, size_t difficulty);

  private:
    struct FieldList
    {
        size_t row;
        size_t col;
    };

    // clang-format off
    inline static const std::map<DifficultyLevel, DifficultyProfile> difficultyMap =
    {
        // { KEY,                  { MIN, MAX, SYMMETRY, ATTEMTS }}
        { DifficultyLevel::EASY,    { 36,  45,  true,   20 } },
        { DifficultyLevel::MEDIUM,  { 46,  51,  true,   50 } },
        { DifficultyLevel::HARD,    { 52,  56,  true,   500 } },
        { DifficultyLevel::EXPERT,  { 57,  64,  false,  2000 } }
    };
    // clang-format on

    std::vector<FieldList> field_list(std::vector<std::vector<int>>& sudoku_table);

    DifficultyLevel selectedLevel(size_t difficulty);

    std::vector<Generate::FieldList> fields;

    std::vector<std::vector<int>> tmp_sudoku_table;

    std::vector<std::vector<int>> unsolved_sudoku;

    size_t empty_fields{};

    size_t attemptsLeft;

    size_t backup;

    size_t backup_sym{};

    size_t solutions{};
};

#endif
