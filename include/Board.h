// SPDX-FileCopyrightText: 2025 thorium1256
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
    std::vector<Cell> getNeighborsOf(int x, int y);

private:
    Vector2 size;
    short mines;
    bool b_gameOver = false;
    bool isFirstClick = true;
    std::vector<std::vector<Cell>> cells;

    bool checkWinCondition() const;
};