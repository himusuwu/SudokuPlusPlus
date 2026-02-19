#include "sudoku_generator.hpp"
#include "sudoku_solver.hpp"
#include "Config.hpp"

std::vector<FieldList> field_list(std::vector<std::vector<int>>& sudoku_table)
{
    std::vector<FieldList> fields;

    for(size_t row = 0; row < sudoku_table.size(); row++)
    {
        for(size_t col = 0; col < sudoku_table[row].size(); col++)
        {
            fields.push_back({row, col});
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(fields.begin(), fields.end(), std::default_random_engine(seed));

    return fields;
}

DifficultyLevel selectedLevel(size_t difficulty)
{
    switch(difficulty)
    {
        case 1:
            return DifficultyLevel::EASY;

        case 2:
            return DifficultyLevel::MEDIUM;

        case 3:
            return DifficultyLevel::HARD;

        case 4:
            return DifficultyLevel::EXPERT;

        default:
            return DifficultyLevel::EASY;
    }
}

std::vector<std::vector<int>> sudoku_generator(std::vector<std::vector<int>>& sudoku_table, size_t difficulty)
{
    std::vector<FieldList> fields = field_list(sudoku_table);

    std::vector<std::vector<int>> tmp_sudoku_table = sudoku_table;

    std::vector<std::vector<int>> unsolved_sudoku;

    size_t empty_fields{};

    const DifficultyProfile& config = difficultyMap.at(selectedLevel(difficulty));

    size_t attemptsLeft = config.solverAttempts;

    for(const auto& field : fields)
    {
        if(empty_fields >= config.maxEmpty || attemptsLeft == 0)
        {
            break;
        }

        if(tmp_sudoku_table[field.row][field.col] == 0)
        {
            continue;
        }

        size_t backup = tmp_sudoku_table[field.row][field.col];
        size_t backup_sym{};

        if(config.symmetric)
        {
            tmp_sudoku_table[field.row][field.col] = 0;

            if(!(field.row == 4 && field.col == 4))
            {
                backup_sym = tmp_sudoku_table[8 - field.row][8 - field.col];
                tmp_sudoku_table[8 - field.row][8 - field.col] = 0;
            }
        }
        else
        {
            tmp_sudoku_table[field.row][field.col] = 0;
        }

        size_t solutions{};

        if(check_unique(tmp_sudoku_table))
        {
            if(config.symmetric && !(field.row == 4 && field.col == 4))
            {
                empty_fields += 2;
            }
            else
            {
                empty_fields++;
            }
        }
        else
        {
            tmp_sudoku_table[field.row][field.col] = backup;

            if(config.symmetric && !(field.row == 4 && field.col == 4))
            {
                tmp_sudoku_table[8 - field.row][8 - field.col] = backup_sym;
            }

            attemptsLeft--;
        }
    }

    return tmp_sudoku_table;
}