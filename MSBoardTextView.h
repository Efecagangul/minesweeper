#pragma once
#include "MinesweeperBoard.h"

class MSBoardTextView
{
    MinesweeperBoard& board;

public:
    MSBoardTextView(MinesweeperBoard& board);
    void display() const;
};