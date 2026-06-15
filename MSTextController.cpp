#include "MSTextController.h"
#include <iostream>

MSTextController::MSTextController(MinesweeperBoard& board, MSBoardTextView& view) : board(board), view(view)
{
}

void MSTextController::play()
{
    while (board.getGameState() == RUNNING)
    {
        view.display();
        
        int action, row, col;
        std::cout << "\n1: Reveal, 2: Flag\nAction: ";
        std::cin >> action;
        std::cout << "Row: ";
        std::cin >> row;
        std::cout << "Col: ";
        std::cin >> col;

        if (action == 1)
        {
            board.revealField(row, col);
        }
        else if (action == 2)
        {
            board.toggleFlag(row, col);
        }
    }

    view.display();

    if (board.getGameState() == FINISHED_WIN)
    {
        std::cout << "\nYOU WIN!\n";
    }
    else if (board.getGameState() == FINISHED_LOSS)
    {
        std::cout << "\nYOU LOSE!\n";
    }
}