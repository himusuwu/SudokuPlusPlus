#include "sudoku_generator.hpp"
#include "sudoku_solver.hpp"
#include "Config.hpp"

std::vector<Generate::FieldList> Generate::field_list(std::vector<std::vector<int>>& sudoku_table)
{
    std::vector<Generate::FieldList> fields;

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

DifficultyLevel Generate::selectedLevel(size_t difficulty)
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

[[nodiscard]] std::vector<std::vector<int>> Generate::sudoku_generator(std::vector<std::vector<int>>& sudoku_table, size_t difficulty)
{
    fields = Generate::field_list(sudoku_table);
    
    tmp_sudoku_table = sudoku_table;

    const DifficultyProfile& config = Generate::difficultyMap.at(selectedLevel(difficulty));

    attemptsLeft = config.solverAttempts;

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

        backup = tmp_sudoku_table[field.row][field.col];

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

        Solver solver;

        if(solver.check_unique(tmp_sudoku_table))
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