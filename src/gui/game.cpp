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

    selectedRow = -1;
    selectedCol = -1;

    while(!WindowShouldClose())
    {
        update();

        draw();
    }
}

void Game::update()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        mousePos = GetMousePosition();

        int relativeX = static_cast<int>(mousePos.x - gridStartX);
        int relativeY = static_cast<int>(mousePos.y - gridStartY);

        int tmpCol = relativeX / cell_size;
        int tmpRow = relativeY / cell_size;

        if(relativeX >= 0 && relativeY >= 0 &&
            tmpRow >= 0 && tmpRow <= 8 &&
            tmpCol >= 0 && tmpCol <= 8)
        {
            if(!isLocked[tmpRow][tmpCol])
            {
                selectedRow = tmpRow;
                selectedCol = tmpCol;
            }
        }
        else
        {
            selectedRow = -1;
            selectedCol = -1;
        }
    }

    if(selectedRow != -1 && selectedCol != -1)
    {
        int pressedKey = GetKeyPressed();

        if(pressedKey >= KEY_ONE && pressedKey <= KEY_NINE)
        {
            sudoku_table[selectedRow][selectedCol] = pressedKey - KEY_ONE + 1;
        }
        else if(pressedKey == KEY_BACKSPACE || pressedKey == KEY_DELETE || pressedKey == KEY_ZERO)
        {
            sudoku_table[selectedRow][selectedCol] = 0;
        }
    }
}

void Game::newGame(size_t difficulty)
{    
    Grid grid;

    sudoku_table = grid.sudoku_grid();

    shuffler.shuffle_board(sudoku_table);

    Generate generate;

    sudoku_table = generate.sudoku_generator(sudoku_table, difficulty);

    isLocked = std::vector<std::vector<bool>>(sudoku_table.size(), std::vector<bool>(sudoku_table[0].size()));

    for(size_t row = 0; row < sudoku_table.size(); row++)
    {
        for(size_t col = 0; col < sudoku_table[row].size(); col++)
        {
            if(sudoku_table[row][col] != 0)
            {
                isLocked[row][col] = true;
            }
            else
            {
                isLocked[row][col] = false;
            }
        }
    }
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(WHITE);

    drawSelection();

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

void Game::drawSelection()
{
    if(selectedRow != -1 && selectedCol != -1)
    {
        float x = gridStartX + selectedCol * cell_size;
        float y = gridStartY + selectedRow * cell_size;

        DrawRectangle(
            static_cast<int>(x), static_cast<int>(y),
            static_cast<int>(cell_size), static_cast<int>(cell_size),
            Color{200, 200, 200, 255}
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

                Color textColor = isLocked[row][col] ? BLACK : BLUE;

                DrawText(
                    text.c_str(),
                    textX, textY,
                    fontSize, textColor
                );
            }
        }
    }
}