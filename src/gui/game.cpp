#include "gui/game.hpp"

#include "raylib.h"
#include "sudoku_generator.hpp"
#include "sudoku_grid.hpp"

#include <chrono>
#include <string>

Game::Game(int width, int height) : screenWidth(width), screenHeight(height)
{
    InitWindow(screenWidth, screenHeight, "Sudoku");
    SetTargetFPS(60);

    cell_size = screenWidth / grid_size;
    gridWidth = cell_size * grid_size;

    gridStartX = (screenWidth - gridWidth) / 2;
    gridStartY = ((screenHeight - screenWidth) / 2) - 100;

    infoStartY = gridStartY - 55;

    startTime = std::chrono::steady_clock::now();
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

    while (!WindowShouldClose())
    {
        if (!isFinished)
        {
            stopClock = false;
            update();
        }
        else
        {
            if (!stopClock)
            {
                endTime = std::chrono::steady_clock::now();
                stopClock = true;
            }
        }

        draw();
    }
}

void Game::update()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        mousePos = GetMousePosition();

        int relativeX = static_cast<int>(mousePos.x - gridStartX);
        int relativeY = static_cast<int>(mousePos.y - gridStartY);

        int tmpCol = relativeX / cell_size;
        int tmpRow = relativeY / cell_size;

        if (relativeX >= 0 && relativeY >= 0 && tmpRow >= 0 && tmpRow <= 8 && tmpCol >= 0 && tmpCol <= 8)
        {
            if (!isLocked[tmpRow][tmpCol] && !isCorrect[tmpRow][tmpCol])
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

    if (selectedRow != -1 && selectedCol != -1)
    {
        numberCheck();

        if (isSudokuSolved())
        {
            isFinished = true;
        }
        else
        {
            isFinished = false;
        }
    }
}

void Game::numberCheck()
{
    int pressedKey = GetKeyPressed();

    if (pressedKey >= KEY_ONE && pressedKey <= KEY_NINE)
    {
        if (solved_table[selectedRow][selectedCol] == pressedKey - KEY_ONE + 1)
        {
            score += 100;
            isError[selectedRow][selectedCol] = false;

            sudoku_table[selectedRow][selectedCol] = pressedKey - KEY_ONE + 1;

            isCorrect[selectedRow][selectedCol] = true;

            selectedRow = -1;
            selectedCol = -1;
        }
        else
        {
            errors++;

            isError[selectedRow][selectedCol] = true;

            sudoku_table[selectedRow][selectedCol] = pressedKey - KEY_ONE + 1;
        }
    }
    else if (pressedKey == KEY_BACKSPACE || pressedKey == KEY_DELETE || pressedKey == KEY_ZERO)
    {
        isError[selectedRow][selectedCol] = false;

        sudoku_table[selectedRow][selectedCol] = 0;
    }
}

bool Game::isSudokuSolved()
{
    if (sudoku_table == solved_table)
    {
        return true;
    }

    return false;
}

void Game::drawError()
{
    for (size_t row = 0; row < isError.size(); row++)
    {
        for (size_t col = 0; col < isError[row].size(); col++)
        {
            if (isError[row][col])
            {
                float x = gridStartX + col * cell_size;
                float y = gridStartY + row * cell_size;

                DrawRectangle(
                    static_cast<int>(x),
                    static_cast<int>(y),
                    static_cast<int>(cell_size),
                    static_cast<int>(cell_size),
                    Color{255, 80, 80, 120}
                );
            }
        }
    }
}

void Game::newGame(size_t difficulty)
{
    Grid grid;

    sudoku_table = grid.sudoku_grid();

    shuffler.shuffle_board(sudoku_table);

    solved_table = sudoku_table;

    Generate generate;

    sudoku_table = generate.sudoku_generator(sudoku_table, difficulty);

    isLocked = std::vector<std::vector<bool>>(sudoku_table.size(), std::vector<bool>(sudoku_table[0].size()));

    isCorrect = std::vector<std::vector<bool>>(sudoku_table.size(), std::vector<bool>(sudoku_table[0].size()));

    isError = std::vector<std::vector<bool>>(sudoku_table.size(), std::vector<bool>(sudoku_table[0].size()));

    for (size_t row = 0; row < sudoku_table.size(); row++)
    {
        for (size_t col = 0; col < sudoku_table[row].size(); col++)
        {
            if (sudoku_table[row][col] != 0)
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

    drawError();

    drawNumbers();

    drawInfo();

    drawButtons();

    drawNumPad();

    EndDrawing();
}

void Game::drawButtons()
{
    // Undo Notes Hints Erase
}

void Game::drawNumPad()
{
    // Numbers from 1-9
    int count = 9;

    int numberWidth = MeasureText("9", screenWidth / 15);

    float slotWidth = static_cast<float>(screenWidth) / count;

    int y = screenHeight - fontSize - 20;

    for (size_t num = 0; num < count; num++)
    {
        const char* text = TextFormat("%d", num + 1);

        int textWidth = MeasureText(text, fontSize);

        float slotCenter = slotWidth * num + slotWidth / 2;

        float x = slotCenter - static_cast<float>(textWidth) / 2;

        DrawText(TextFormat("%d", num + 1), x, y, fontSize, BLACK);
    }
}

void Game::drawInfo()
{
    const char* months[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

    auto now = std::chrono::system_clock::now();
    auto days = std::chrono::floor<std::chrono::days>(now);
    std::chrono::year_month_day ymd{days};

    const char* month = months[unsigned(ymd.month()) - 1];

    date = std::to_string(unsigned(ymd.day())) + " " + month;

    std::string s_score = std::to_string(score);

    std::string s_errors = std::to_string(errors) + "/3";

    auto currentTime = std::chrono::steady_clock::now();
    auto elapsed = currentTime - startTime;
    long long seconds;

    if (isFinished)
    {
        elapsed = endTime - startTime;
        seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
    }
    else
    {
        elapsed = currentTime - startTime;
        seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
    }

    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;

    std::string s_time = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + (remainingSeconds < 10 ? "0" : "")
                       + std::to_string(remainingSeconds);

    const int font = 25;
    const int lineGap = 4;
    const int columns = 4;
    const float columntWidth = static_cast<float>(gridWidth) / columns;

    auto drawBlock = [&](int col, const std::string& line1, const std::string& line2) -> void
    {
        float x0 = static_cast<float>(gridStartX) + col * columntWidth;

        int w1 = MeasureText(line1.c_str(), font);
        int w2 = MeasureText(line2.c_str(), font);

        int x1 = static_cast<int>(x0 + (columntWidth - w1) * 0.5f);
        int x2 = static_cast<int>(x0 + (columntWidth - w2) * 0.5f);

        int y1 = infoStartY;
        int y2 = infoStartY + font + lineGap;

        DrawText(line1.c_str(), x1, y1, font, BLACK);
        DrawText(line2.c_str(), x2, y2, font, BLACK);
    };

    drawBlock(0, "Date:", date);
    drawBlock(1, "Score:", s_score);
    drawBlock(2, "Errors:", s_errors);
    drawBlock(3, "Time:", s_time);
}

void Game::drawGrid()
{
    for (size_t i = 0; i <= 9; i++)
    {
        float thickness = (i % 3 == 0) ? 3 : 1;

        float x = gridStartX + i * cell_size;

        DrawLineEx(
            Vector2{x, static_cast<float>(gridStartY)},
            Vector2{x, static_cast<float>(gridStartY + gridWidth)},
            thickness,
            BLACK
        );

        float y = gridStartY + i * cell_size;

        DrawLineEx(
            Vector2{static_cast<float>(gridStartX), y},
            Vector2{static_cast<float>(gridStartX + gridWidth), y},
            thickness,
            BLACK
        );
    }
}

void Game::drawSelection()
{
    if (selectedRow != -1 && selectedCol != -1)
    {
        float x = gridStartX + selectedCol * cell_size;
        float y = gridStartY + selectedRow * cell_size;

        DrawRectangle(
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(cell_size),
            static_cast<int>(cell_size),
            Color{200, 200, 200, 255}
        );
    }
}

void Game::drawNumbers()
{
    Font font = GetFontDefault();

    for (size_t row = 0; row < sudoku_table.size(); row++)
    {
        for (size_t col = 0; col < sudoku_table[row].size(); col++)
        {
            int number = sudoku_table[row][col];

            if (number != 0)
            {
                int cellX = gridStartX + col * cell_size;
                int cellY = gridStartY + row * cell_size;

                float centerX = cellX + cell_size / 2.0f;
                float centerY = cellY + cell_size / 2.0f;

                std::string text = std::to_string(number);

                Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);

                float textX = centerX - textSize.x / 2;
                float textY = centerY - textSize.y / 2;

                Color textColor = isLocked[row][col] ? BLACK : !isCorrect[row][col] ? RED : GREEN;

                DrawText(text.c_str(), textX, textY, fontSize, textColor);
            }
        }
    }
}
