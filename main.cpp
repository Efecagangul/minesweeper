#include <iostream>
#include "MinesweeperBoard.h"

int main()
{
    std::cout << "=== Default board ===\n";
    MinesweeperBoard board1;
    board1.debug_display();

    std::cout << "\n=== DEBUG mode 9x7 ===\n";
    MinesweeperBoard board2(9, 7, DEBUG);
    board2.debug_display();

    std::cout << "\n=== EASY mode 5x5 ===\n";
    MinesweeperBoard board3(5, 5, EASY);
    board3.debug_display();

    return 0;
}
