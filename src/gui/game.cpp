#include "gui/game.hpp"

Game::Game(int width, int height) : screenWidth(width), screenHeight(height)
{
    InitWindow(screenWidth, screenHeight, "Sudoku");
    SetTargetFPS(60);

    cell_size = screenWidth / grid_size;
    gridWidth = cell_size * grid_size;

    gridStartX = (screenWidth - gridWidth) / 2;
    gridStartY = (screenHeight - screenWidth) / 2;
}

Game::~Game()
{
    CloseWindow();
}

void Game::run()
{
    newGame(1);

    while(!WindowShouldClose())
    {
        draw();
    }
}

void Game::newGame(size_t difficulty)
{    
    Grid grid;

    sudoku_table = grid.sudoku_grid();

    shuffler.shuffle_board(sudoku_table);

    Generate generate;

    sudoku_table = generate.sudoku_generator(sudoku_table, difficulty);
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(WHITE);

    drawGrid();

    drawNumbers();

    EndDrawing();
}

void Game::drawGrid()
{
    for(size_t i = 0; i <= 9; i++)
    {
        float thickness = (i % 3 == 0) ? 3 : 1;

        float x = gridStartX + i * cell_size;

        DrawLineEx(
            Vector2{x, static_cast<float>(gridStartY)},
            Vector2{x, static_cast<float>(gridStartY + gridWidth)},
            thickness, BLACK
        );

        float y = gridStartY + i * cell_size;

        DrawLineEx(
            Vector2{static_cast<float>(gridStartX), y},
            Vector2{static_cast<float>(gridStartX + gridWidth), y},
            thickness, BLACK
        );
    }
}

void Game::drawNumbers()
{
    Font font = GetFontDefault();

    for(size_t row = 0; row < sudoku_table.size(); row++)
    {
        for(size_t col = 0; col < sudoku_table[row].size(); col++)
        {
            int number = sudoku_table[row][col];

            if(number != 0)
            {
                int cellX = gridStartX + col * cell_size;
                int cellY = gridStartY + row * cell_size;

                float centerX = cellX + cell_size / 2.0f;
                float centerY = cellY + cell_size / 2.0f;

                std::string text = std::to_string(number);

                Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);

                float textX = centerX - textSize.x / 2;
                float textY = centerY - textSize.y / 2;

                DrawText(
                    text.c_str(),
                    textX, textY,
                    fontSize, BLACK
                );
            }
        }
    }
}