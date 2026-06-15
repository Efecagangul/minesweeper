#include "MinesweeperBoard.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

MinesweeperBoard::MinesweeperBoard()
{
    width  = 5;
    height = 7;
    clearBoard();
    applyDefaultLayout();
}

MinesweeperBoard::MinesweeperBoard(int w, int h, GameMode mode)
{
    width  = (w > 0 && w <= 100) ? w : 10;
    height = (h > 0 && h <= 100) ? h : 10;
    clearBoard();

    switch (mode)
    {
        case EASY:   placeRandomMines((int)std::ceil(width * height * 0.10)); break;
        case NORMAL: placeRandomMines((int)std::ceil(width * height * 0.20)); break;
        case HARD:   placeRandomMines((int)std::ceil(width * height * 0.30)); break;
        case DEBUG:  placeDebugMines(); break;
    }
}

int MinesweeperBoard::getBoardWidth()  const { return width; }
int MinesweeperBoard::getBoardHeight() const { return height; }

void MinesweeperBoard::debug_display() const
{
    std::cout << "   ";
    for (int c = 0; c < width; ++c)
        std::cout << std::setw(4) << c << " ";
    std::cout << "\n";

    for (int r = 0; r < height; ++r)
    {
        std::cout << std::setw(2) << r << " ";
        for (int c = 0; c < width; ++c)
        {
            const Field& f = board[r][c];
            std::cout << "[" << (f.hasMine ? 'M' : '.') << (f.isRevealed ? 'r' : '.') << (f.hasFlag ? 'f' : '.') << "]";
        }
        std::cout << "\n";
    }
}

bool MinesweeperBoard::isValidPosition(int row, int col) const
{
    return row >= 0 && row < height && col >= 0 && col < width;
}

void MinesweeperBoard::clearBoard()
{
    for (int r = 0; r < height; ++r)
        for (int c = 0; c < width; ++c)
            board[r][c] = {false, false, false};
}

void MinesweeperBoard::applyDefaultLayout()
{
    if (isValidPosition(0, 0)) board[0][0].hasMine    = true;
    if (isValidPosition(1, 1)) board[1][1].isRevealed = true;
    if (isValidPosition(0, 2)) { board[0][2].hasMine = true; board[0][2].hasFlag = true; }
}

void MinesweeperBoard::placeRandomMines(int count)
{
    static bool seeded = false;
    if (!seeded) { std::srand((unsigned)std::time(nullptr)); seeded = true; }

    int placed = 0;
    while (placed < count)
    {
        int r = std::rand() % height;
        int c = std::rand() % width;
        if (!board[r][c].hasMine)
        {
            board[r][c].hasMine = true;
            ++placed;
        }
    }
}

void MinesweeperBoard::placeDebugMines()
{
    for (int c = 0; c < width; ++c)
        board[0][c].hasMine = true;

    for (int i = 0; i < height && i < width; ++i)
        board[i][i].hasMine = true;

    for (int r = 0; r < height; r += 2)
        board[r][0].hasMine = true;
}
