#include "MinesweeperBoard.h"

MinesweeperBoard::MinesweeperBoard()
{
    width  = 5;
    height = 7;
    clearBoard();
    applyDefaultLayout();
}

int MinesweeperBoard::getBoardWidth()  const { return width; }
int MinesweeperBoard::getBoardHeight() const { return height; }

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
