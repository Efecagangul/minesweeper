#pragma once

#include "Field.h"

class MinesweeperBoard
{
    Field board[100][100];
    int width;
    int height;

    bool isValidPosition(int row, int col) const;
    void clearBoard();
    void applyDefaultLayout();

public:
    MinesweeperBoard();

    int getBoardWidth()  const;
    int getBoardHeight() const;
};
