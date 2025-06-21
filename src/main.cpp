#include <iostream>
#include <stdexcept>
#include <ncursesw/ncurses.h>
#include <ctime>
#include <unistd.h>
#include "Board.h"

#define MAX_TIME 60

void startGame(Board &board)
{
    int minesLeft = board.getMineCount();

    Vector2 boardSize = board.getBoardSize();
    int c;
    int cursorX = 0, cursorY = 0;

    refresh();
    bool gameRunning = true;

    time_t startTime = time(nullptr);
    int elapsedTime = 0;

    bool isPaused = false;
    time_t startPauseTime = 0;
    time_t pauseTime = 0;
    time_t totalpausetime = 0;
    while (gameRunning)
    {

        usleep((1000 / MAX_TIME) * 1000);
        if (board.isGameOver() || board.isGameWon())
        {
            gameRunning = false;
        }
        if (!isPaused)
            elapsedTime = difftime(time(NULL), startTime) - totalpausetime;
        char flags[5];
        char tim[5];
        sprintf(flags, "%03d", minesLeft);
        sprintf(tim, "%03d", elapsedTime);
        attron(COLOR_PAIR(3));
        mvprintw(1, 1, "%s", flags);
        attroff(COLOR_PAIR(3));
        if (!isPaused)
            mvprintw(1, 5, ":)");
        else
            mvprintw(1, 5, ":|");
        attron(COLOR_PAIR(3));
        mvprintw(1, 8, "%s", tim);
        attroff(COLOR_PAIR(3));
        refresh();

        for (int y = 0; y < boardSize.y; y++)
        {
            for (int x = 0; x < boardSize.x; x++)
            {
                Cell::State state = board.getCellStateAt(x, y);

                char displayChar = ' ';
                if (state == Cell::State::Flagged)
                {
                    displayChar = 'F';
                }
                else if (state == Cell::State::Revealed)
                {
                    Cell::Content content = board.revealCellAt(x, y).getContent();
                    if (content == Cell::Content::Mine)
                    {
                        attron(COLOR_PAIR(7));
                        displayChar = '+';
                    }
                    else if (content != Cell::Content::Empty)
                    {
                        displayChar = '0' + static_cast<int>(content);
                    }
                }
                else if (state == Cell::State::Hidden)
                {
                    displayChar = '#';
                }
                else if (state == Cell::State::NotAMine)
                {
                    displayChar = 'X';
                }

                if (isPaused)
                    displayChar = '#';

                if (x == cursorX && y == cursorY)
                {
                    attron(A_REVERSE);
                }

                if (displayChar == 'F')
                {
                    attron(COLOR_PAIR(9));
                }

                if (displayChar >= '1' && displayChar <= '8')
                {
                    attron(COLOR_PAIR(displayChar - '0'));
                }
                if (displayChar == 'X')
                {
                    attron(COLOR_PAIR(9));
                }

                mvaddch(y + 2, x + 1, displayChar);

                if (displayChar == 'X')
                {
                    attroff(COLOR_PAIR(9));
                }

                if (displayChar >= '1' && displayChar <= '8')
                {
                    attroff(COLOR_PAIR(displayChar - '0'));
                }

                if (displayChar == 'F')
                {
                    attroff(COLOR_PAIR(9));
                }

                if (displayChar == '+')
                {
                    attroff(COLOR_PAIR(7));
                }

                if (x == cursorX && y == cursorY)
                {
                    attroff(A_REVERSE);
                }
            }
        }

        c = getch();
        if (c == ERR)
            continue;

        switch (c)
        {
        case KEY_UP:
            cursorY = (cursorY > 0) ? cursorY - 1 : boardSize.y - 1;
            break;
        case KEY_DOWN:
            cursorY = (cursorY < boardSize.y - 1) ? cursorY + 1 : 0;
            break;
        case KEY_LEFT:
            cursorX = (cursorX > 0) ? cursorX - 1 : boardSize.x - 1;
            break;
        case KEY_RIGHT:
            cursorX = (cursorX < boardSize.x - 1) ? cursorX + 1 : 0;
            break;
        case 'q':
            return;
            break;
        case 'z':
            board.revealCellAt(cursorX, cursorY);
            break;
        case 'x':
            if (board.getCellStateAt(cursorX, cursorY) == Cell::State::Flagged)
            {
                minesLeft++;
            }
            else
            {
                minesLeft--;
            }
            board.flagCellAt(cursorX, cursorY);
            break;
        case 'r':
            startTime = time(NULL);
            board.regenerateBoard();
            somethingHasBeenDone = false;
            elapsedTime = 0;
            break;
        case 'p':
            if (isPaused)
            {
                pauseTime = difftime(time(NULL), startPauseTime);
                totalpausetime += pauseTime;
            }
            else
            {
                startPauseTime = time(NULL);
            }
            isPaused = !isPaused;
        }

        if (isPaused)
            continue;

        refresh();
    }

    if (board.isGameOver())
    {
        char flags[3];
        char tim[3];
        sprintf(flags, "%03d", minesLeft);
        sprintf(tim, "%03d", elapsedTime);
        attron(COLOR_PAIR(3));
        mvprintw(1, 1, "%s", flags);
        attroff(COLOR_PAIR(3));
        mvprintw(1, 5, "X(");
        attron(COLOR_PAIR(3));
        mvprintw(1, 8, "%s", tim);
        attroff(COLOR_PAIR(3));
        refresh();
        while ((c = getch()) != 'q')
        {
            if (c == 'r')
            {
                Board newBoard(boardSize.x, boardSize.y, board.getMineCount());
                startGame(newBoard);
            }
        };
    }
    else if (board.isGameWon())
    {
        char flags[3];
        char tim[3];
        sprintf(flags, "%03d", minesLeft);
        sprintf(tim, "%03d", elapsedTime);
        attron(COLOR_PAIR(3));
        mvprintw(1, 1, "%s", flags);
        attroff(COLOR_PAIR(3));
        mvprintw(1, 5, "B)");
        attron(COLOR_PAIR(3));
        mvprintw(1, 8, "%s", tim);
        attroff(COLOR_PAIR(3));
        refresh();
        int c;
        while ((c = getch()) != 'q')
        {
            if (c == 'r')
            {
                Board newBoard(boardSize.x, boardSize.y, board.getMineCount());
                startGame(newBoard);
            }
        };
    }
}

int main()
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
    init_pair(9, COLOR_RED, COLOR_WHITE);

    int choice = 0;
    int max_choice = 2;
    curs_set(0);

    while (true)
    {
        usleep((1000 / MAX_TIME) * 1000);

        mvprintw(1, 1, "Select a difficulty:");
        attron(A_REVERSE);
        mvprintw(2, 2, choice == 0 ? "Beginner (9x9, 10 mines)" : "");
        attroff(A_REVERSE);
        mvprintw(2, 2, choice == 0 ? "" : "Beginner (9x9, 10 mines)");
        attron(A_REVERSE);
        mvprintw(3, 2, choice == 1 ? "Intermediate (16x16, 40 mines)" : "");
        attroff(A_REVERSE);
        mvprintw(3, 2, choice == 1 ? "" : "Intermediate (16x16, 40 mines)");
        attron(A_REVERSE);
        mvprintw(4, 2, choice == 2 ? "Expert (16x30, 99 mines)" : "");
        attroff(A_REVERSE);
        mvprintw(4, 2, choice == 2 ? "" : "Expert (16x30, 99 mines)");
        refresh();

        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice = (choice > 0) ? choice - 1 : max_choice;
            break;
        case KEY_DOWN:
            choice = (choice < max_choice) ? choice + 1 : 0;
            break;
        case '\n':
            int w, h, mines;
            if (choice == 0)
            {
                w = 9;
                h = 9;
                mines = 10;
            }
            else if (choice == 1)
            {
                w = 16;
                h = 16;
                mines = 40;
            }
            else
            {
                w = 16;
                h = 30;
                mines = 99;
            }
            Board board(w, h, mines);
            clear();
            startGame(board);
            curs_set(2);
            endwin();
            return 0;
        }
    }
}
