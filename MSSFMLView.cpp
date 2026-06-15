#include "MSSFMLView.h"

MSSFMLView::MSSFMLView(MinesweeperBoard& board) : board(board)
{
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

    tile.setSize(sf::Vector2f(30.f, 30.f));
    tile.setOutlineThickness(2.f);
    tile.setOutlineColor(sf::Color::Black);
}

void MSSFMLView::draw(sf::RenderWindow& window)
{
    for (int r = 0; r < board.getBoardHeight(); ++r)
    {
        for (int c = 0; c < board.getBoardWidth(); ++c)
        {
            float x = c * 32.f;
            float y = r * 32.f;

            tile.setPosition(x, y);
            char info = board.getFieldInfo(r, c);

            if (info == '_')
            {
                tile.setFillColor(sf::Color(150, 150, 150));
                window.draw(tile);
            }
            else if (info == 'F')
            {
                tile.setFillColor(sf::Color::Blue);
                window.draw(tile);
            }
            else if (info == 'x')
            {
                tile.setFillColor(sf::Color::Red);
                window.draw(tile);
            }
            else if (info == ' ')
            {
                tile.setFillColor(sf::Color(200, 200, 200));
                window.draw(tile);
            }
            else
            {
                tile.setFillColor(sf::Color(200, 200, 200));
                window.draw(tile);
                text.setString(std::string(1, info));
                text.setPosition(x + 8.f, y + 2.f);
                window.draw(text);
            }
        }
    }
}