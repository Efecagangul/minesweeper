#include "MSSFMLController.h"

MSSFMLController::MSSFMLController(MinesweeperBoard& board) : board(board)
{
}

void MSSFMLController::handleEvent(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        int col = event.mouseButton.x / 32;
        int row = event.mouseButton.y / 32;

        if (event.mouseButton.button == sf::Mouse::Left)
        {
            board.revealField(row, col);
        }
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
            board.toggleFlag(row, col);
        }
    }
}