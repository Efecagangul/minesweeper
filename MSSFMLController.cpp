#include "MSSFMLController.h"

MSSFMLController::MSSFMLController(MinesweeperBoard& board) : board(board)
{
}

void MSSFMLController::handleEvent(const sf::Event& event)
{
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        const auto& mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseEvent)
        {
            int col = static_cast<int>(mouseEvent->position.x) / 32;
            int row = static_cast<int>(mouseEvent->position.y) / 32;

            if (mouseEvent->button == sf::Mouse::Button::Left)
            {
                board.revealField(row, col);
            }
            else if (mouseEvent->button == sf::Mouse::Button::Right)
            {
                board.toggleFlag(row, col);
            }
        }
    }
}