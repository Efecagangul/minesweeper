#pragma once

#include "Field.h"
#include "GameMode.h"

class MinesweeperBoard
{
    Field board[100][100];
    int width;
    int height;

    bool isValidPosition(int row, int col) const;
    void clearBoard();
    void applyDefaultLayout();
    void placeRandomMines(int count);
    void placeDebugMines();

public:
    MinesweeperBoard();
    MinesweeperBoard(int width, int height, GameMode mode);

    int getBoardWidth()  const;
    int getBoardHeight() const;

    void debug_display() const;
};
