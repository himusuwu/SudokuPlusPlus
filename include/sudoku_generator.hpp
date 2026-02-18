#ifndef SUDOKU_GENERATOR
#define SUDOKU_GENERATOR

#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>

struct FieldList
{
    size_t row;
    size_t col;
};

std::vector<FieldList> sudoku_generator(std::vector<std::vector<int>>& sudoku_table);
std::vector<FieldList> field_list(std::vector<std::vector<int>>& sudoku_table);

#endif