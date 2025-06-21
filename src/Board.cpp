#include "Board.h"
#include <iostream>

Board::Board(int w, int h, short mines) : size(w, h), mines(mines), isFirstClick(true), b_gameOver(false)
{
    cells.resize(h);
    for (int y = 0; y < h; y++)
    {
        cells[y].resize(w);
        for (int x = 0; x < w; x++)
        {
            cells[y][x] = Cell(x, y);
        }
    }

    std::vector<Vector2> positions;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            positions.push_back(Vector2(x, y));
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);

    for (int i = 0; i < mines; i++)
    {
        Vector2 pos = positions[i];
        cells[pos.y][pos.x].setContent(Cell::Content::Mine);
    }

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            Cell &cell = cells[y][x];
            if (cell.getContent() != Cell::Content::Mine)
            {
                int count = 0;
                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        if (dx == 0 && dy == 0)
                            continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < w && ny >= 0 && ny < h)
                        {
                            if (cells[ny][nx].getContent() == Cell::Content::Mine)
                            {
                                count++;
                            }
                        }
                    }
                }
                cell.setContent(static_cast<Cell::Content>(count));
            }
        }
    }
}

bool Board::isGameOver()
{
    return b_gameOver;
}

Cell Board::revealCellAt(int x, int y)
{
    if (x < 0 || x >= size.x || y < 0 || y >= size.y)
    {
        throw std::out_of_range("Cell coordinates out of bounds");
    }

    Cell &cell = cells[y][x];
    if (cell.getState() == Cell::State::Revealed || cell.getState() == Cell::State::Flagged)
    {
        return cell;
    }

    if (isFirstClick)
    {
        if (cell.getContent() == Cell::Content::Mine)
        {
            regenerateBoard();
            return revealCellAt(x, y);
        }
        isFirstClick = false;
    }

    if (cell.getContent() == Cell::Content::Mine)
    {
        cell.reveal();
        gameOver();
        return cell;
    }

    if (cell.getContent() == Cell::Content::Empty)
    {
        revealEmptyCells(x, y);
    }
    else
    {
        cell.reveal();
    }

    return cell;
}

void Board::revealEmptyCells(int x, int y)
{
    std::queue<Vector2> q;
    q.push(Vector2(x, y));

    while (!q.empty())
    {
        Vector2 pos = q.front();
        q.pop();

        Cell &current = cells[pos.y][pos.x];
        if (current.getState() != Cell::State::Hidden)
        {
            continue;
        }

        current.reveal();

        if (current.getContent() == Cell::Content::Empty)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0)
                        continue;
                    int nx = pos.x + dx;
                    int ny = pos.y + dy;
                    if (nx >= 0 && nx < size.x && ny >= 0 && ny < size.y)
                    {
                        Cell &neighbor = cells[ny][nx];
                        if (neighbor.getState() == Cell::State::Hidden)
                        {
                            q.push(Vector2(nx, ny));
                        }
                    }
                }
            }
        }
    }
}

void Board::gameOver()
{
    b_gameOver = true;
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            Cell &cell = cells[y][x];
            if (cell.getContent() == Cell::Content::Mine &&
                cell.getState() != Cell::State::Flagged)
            {
                cell.reveal();
            }
            if (cell.getContent() != Cell::Content::Mine && cell.getState() == Cell::State::Flagged)
            {
                cell.state = Cell::State::NotAMine;
            }
        }
    }
}

void Board::flagCellAt(int x, int y)
{
    if (x < 0 || x >= size.x || y < 0 || y >= size.y)
    {
        return;
    }
    cells[y][x].toggleFlag();
}

Vector2 Board::getBoardSize() const
{
    return size;
}

void Board::regenerateBoard()
{
    cells.clear();
    isFirstClick = true;

    cells.resize(size.y);
    for (int y = 0; y < size.y; y++)
    {
        cells[y].resize(size.x);
        for (int x = 0; x < size.x; x++)
        {
            cells[y][x] = Cell(x, y);
        }
    }

    std::vector<Vector2> positions;
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            positions.push_back(Vector2(x, y));
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);

    for (int i = 0; i < mines; i++)
    {
        Vector2 pos = positions[i];
        cells[pos.y][pos.x].setContent(Cell::Content::Mine);
    }

    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            Cell &cell = cells[y][x];
            if (cell.getContent() != Cell::Content::Mine)
            {
                int count = 0;
                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        if (dx == 0 && dy == 0)
                            continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < size.x && ny >= 0 && ny < size.y)
                        {
                            if (cells[ny][nx].getContent() == Cell::Content::Mine)
                            {
                                count++;
                            }
                        }
                    }
                }
                cell.setContent(static_cast<Cell::Content>(count));
            }
        }
    }
}

int Board::getMineCount() const
{
    return mines;
}

Cell::State Board::getCellStateAt(int x, int y)
{
    return cells[y][x].getState();
}

bool Board::isGameWon() const
{
    return checkWinCondition();
}

bool Board::checkWinCondition() const
{
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            const Cell &cell = cells[y][x];
            if (cell.getContent() != Cell::Content::Mine && cell.getState() != Cell::State::Revealed)
            {
                return false;
            }
        }
    }
    return true;
}
