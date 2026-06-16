#include "MinesweeperBoard.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>

MinesweeperBoard::MinesweeperBoard()
{
    width     = 5;
    height    = 7;
    gameState = RUNNING;
    firstMove = true;
    debugMode = false;
    clearBoard();
    applyDefaultLayout();
}

MinesweeperBoard::MinesweeperBoard(int w, int h, GameMode mode)
{
    width     = (w > 0 && w <= 100) ? w : 10;
    height    = (h > 0 && h <= 100) ? h : 10;
    gameState = RUNNING;
    firstMove = true;
    debugMode = (mode == DEBUG);
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

int MinesweeperBoard::getMineCount() const
{
    int count = 0;
    for (int r = 0; r < height; ++r)
        for (int c = 0; c < width; ++c)
            if (board[r][c].hasMine) ++count;
    return count;
}

int MinesweeperBoard::countMines(int row, int col) const
{
    if (!isValidPosition(row, col))      return -1;
    if (!board[row][col].isRevealed)     return -1;

    int count = 0;
    for (int dr = -1; dr <= 1; ++dr)
        for (int dc = -1; dc <= 1; ++dc)
        {
            if (dr == 0 && dc == 0) continue;
            int nr = row + dr;
            int nc = col + dc;
            if (isValidPosition(nr, nc) && board[nr][nc].hasMine)
                ++count;
        }
    return count;
}

bool MinesweeperBoard::hasFlag(int row, int col) const
{
    if (!isValidPosition(row, col))  return false;
    if (board[row][col].isRevealed) return false;
    return board[row][col].hasFlag;
}

bool MinesweeperBoard::isRevealed(int row, int col) const
{
    if (!isValidPosition(row, col)) return false;
    return board[row][col].isRevealed;
}

void MinesweeperBoard::toggleFlag(int row, int col)
{
    if (!isValidPosition(row, col))  return;
    if (board[row][col].isRevealed) return;
    if (gameState != RUNNING)        return;
    board[row][col].hasFlag = !board[row][col].hasFlag;
}

void MinesweeperBoard::revealField(int row, int col)
{
    if (!isValidPosition(row, col))  return;
    if (board[row][col].isRevealed) return;
    if (board[row][col].hasFlag)    return;
    if (gameState != RUNNING)        return;

    if (board[row][col].hasMine)
    {
        if (firstMove && !debugMode)
        {
            relocateMine(row, col);
            firstMove = false;
            board[row][col].isRevealed = true;
        }
        else
        {
            board[row][col].isRevealed = true;
            gameState = FINISHED_LOSS;
        }
        // Reveal all mines when the game is lost so the view can show them
        if (gameState == FINISHED_LOSS)
        {
            for (int r = 0; r < height; ++r)
                for (int c = 0; c < width; ++c)
                    if (board[r][c].hasMine)
                        board[r][c].isRevealed = true;
        }
    }
    else
    {
        firstMove = false;
        board[row][col].isRevealed = true;
        if (countMines(row, col) == 0)
            floodReveal(row, col);
    }

    if (gameState == RUNNING)
    {
        for (int r = 0; r < height; ++r)
            for (int c = 0; c < width; ++c)
                if (!board[r][c].hasMine && !board[r][c].isRevealed)
                    return;
        gameState = FINISHED_WIN;
    }
}

GameState MinesweeperBoard::getGameState() const
{
    return gameState;
}

char MinesweeperBoard::getFieldInfo(int row, int col) const
{
    if (!isValidPosition(row, col))     return '#';
    if (!board[row][col].isRevealed)
    {
        if (board[row][col].hasFlag)    return 'F';
        return '_';
    }
    if (board[row][col].hasMine)        return 'x';
    int mines = countMines(row, col);
    if (mines == 0)                     return ' ';
    return '0' + mines;
}

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
    static std::random_device rd;
    static std::mt19937 generator(rd());

    int placed = 0;
    while (placed < count)
    {
        std::uniform_int_distribution<int> distHeight(0, height - 1);
        std::uniform_int_distribution<int> distWidth(0, width - 1);
        
        int r = distHeight(generator);
        int c = distWidth(generator);
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

void MinesweeperBoard::relocateMine(int row, int col)
{
    static std::random_device rd;
    static std::mt19937 generator(rd()); // saw it online once now its my go to for random numbers

    board[row][col].hasMine = false;
    int r, c;
    do {
        std::uniform_int_distribution<int> distHeight(0, height - 1);
        std::uniform_int_distribution<int> distWidth(0, width - 1);
        
        r = distHeight(generator);
        c = distWidth(generator);
    } while (board[r][c].hasMine || (r == row && c == col));
    board[r][c].hasMine = true;
}

void MinesweeperBoard::floodReveal(int row, int col)
{
    for (int dr = -1; dr <= 1; ++dr)
        for (int dc = -1; dc <= 1; ++dc)
        {
            if (dr == 0 && dc == 0) continue;
            int nr = row + dr;
            int nc = col + dc;
            if (!isValidPosition(nr, nc)) continue;
            if (board[nr][nc].isRevealed) continue;
            if (board[nr][nc].hasFlag) continue;
            if (board[nr][nc].hasMine) continue;

            board[nr][nc].isRevealed = true;
            if (countMines(nr, nc) == 0)
                floodReveal(nr, nc);
        }
}
