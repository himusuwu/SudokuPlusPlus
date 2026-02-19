#ifndef SUDOKU_GENERATOR
#define SUDOKU_GENERATOR

#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <map>

#include "Config.hpp"

inline const std::map<DifficultyLevel, DifficultyProfile> difficultyMap =
{
    // { KEY,                  { MIN, MAX, SYMETRY, ATTEMTS }}
    { DifficultyLevel::EASY,    { 36,  45,  true,   20 } },
    { DifficultyLevel::MEDIUM,  { 46,  51,  true,   50 } },
    { DifficultyLevel::HARD,    { 52,  56,  true,   500 } },
    { DifficultyLevel::EXPERT,  { 57,  64,  false,  2000 } }
};

struct FieldList
{
    size_t row;
    size_t col;
};

std::vector<std::vector<int>> sudoku_generator(std::vector<std::vector<int>>& sudoku_table, size_t difficulty);

#endif