#include "MSBoardTextView.h"
#include <iostream>

MSBoardTextView::MSBoardTextView(MinesweeperBoard& board) : board(board)
{
}

void MSBoardTextView::display() const
{
    for (int r = 0; r < board.getBoardHeight(); ++r)
    {
        for (int c = 0; c < board.getBoardWidth(); ++c)
        {
            std::cout << "[" << board.getFieldInfo(r, c) << "]";
        }
        std::cout << "\n";
    }
}