#ifndef GAME
#define GAME

#include "shuffle_board.hpp"

#include <raylib.h>
#include <vector>

class Game
{
  public:
    Game(int width, int height);
    ~Game();

    void run();

  private:
    void newGame(size_t difficulty);
    void draw();
    void drawGrid();
    void drawNumbers();
    void drawSelection();
    void update();
    void drawInfo();
    void drawButtons();
    void numberCheck();
    void drawError();

    int screenWidth;
    int screenHeight;
    int cell_size;
    int gridStartX;
    int gridStartY;
    int gridWidth;

    const float fontSize = 40;
    const float spacing = 1;
    const int grid_size = 9;

    std::vector<std::vector<int>> sudoku_table;

    std::vector<std::vector<int>> solved_table;

    std::vector<std::vector<bool>> isLocked;
    std::vector<std::vector<bool>> isCorrect;
    std::vector<std::vector<bool>> isError;

    Vector2 mousePos;
    bool cellSelected;
    size_t selectedRow;
    size_t selectedCol;
    size_t keyboardNum;

    // Draw info
    std::string date;
    int score{};
    size_t errors{};
    int time;

    int infoStartX;
    int infoStartY;

    std::chrono::steady_clock::time_point startTime{};

    Shuffler shuffler;
};

#endif
