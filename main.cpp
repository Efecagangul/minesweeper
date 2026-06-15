#include <iostream>
#include "MinesweeperBoard.h"

int main()
{
    MinesweeperBoard board;
    std::cout << "Width:  " << board.getBoardWidth()  << "\n";
    std::cout << "Height: " << board.getBoardHeight() << "\n";
    return 0;
}
