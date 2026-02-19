#ifndef GAME
#define GAME

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
};

#endif