#pragma once
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
#include <stdexcept>
#include "Cell.h"

class Board
{
public:
    Board(int w, int h, short mines);
    Cell revealCellAt(int x, int y);
    void gameOver();
    void flagCellAt(int x, int y);
    Vector2 getBoardSize() const;
    bool isGameOver();
    void revealEmptyCells(int x, int y);
    Cell::State getCellStateAt(int x, int y);
    int getMineCount() const;
    void regenerateBoard();
    bool isGameWon() const;

private:
    Vector2 size;
    short mines;
    bool b_gameOver = false;
    bool isFirstClick = true;
    std::vector<std::vector<Cell>> cells;

    bool checkWinCondition() const;
};