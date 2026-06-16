#include "MSTextController.h"
#include <iostream>
#include <limits>

MSTextController::MSTextController(MinesweeperBoard& board, MSBoardTextView& view) : board(board), view(view)
{
}

void MSTextController::play()
{
    while (board.getGameState() == RUNNING)
    {
        view.display();

        int action = -1;
        int row = -1;
        int col = -1;

        // action input with validation
        while (true)
        {
            std::cout << "\n1: Reveal, 2: Flag, 0: Quit\nAction: ";
            if (!(std::cin >> action))
            {
                if (std::cin.eof()) return;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid action. Please enter 1, 2 or 0.\n";
                continue;
            }
            if (action == 0) { std::cout << "Quitting.\n"; return; }
            if (action == 1 || action == 2) break;
            std::cout << "Action must be 1 or 2 (or 0 to quit).\n";
        }

        //  row,c input with validation
        while (true)
        {
            std::cout << "Row: ";
            if (!(std::cin >> row))
            {
                if (std::cin.eof()) return;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid row. Please enter an integer.\n";
                continue;
            }

            std::cout << "Col: ";
            if (!(std::cin >> col))
            {
                if (std::cin.eof()) return;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid col. Please enter an integer.\n";
                continue;
            }

            if (row < 0 || row >= board.getBoardHeight() || col < 0 || col >= board.getBoardWidth())
            {
                std::cout << "Position out of bounds. Try again.\n";
                continue;
            }

            break;
        }

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