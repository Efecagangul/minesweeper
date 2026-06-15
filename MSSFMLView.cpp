#include "MSSFMLView.h"
#include <iostream>

MSSFMLView::MSSFMLView(MinesweeperBoard& board) : board(board)
{
    font = std::make_shared<sf::Font>();
    if (!font->openFromFile("arial.ttf"))
    {
        std::cerr << "Warning: Could not load arial.ttf\n";
    }
    
    text = std::make_shared<sf::Text>(*font);
    text->setCharacterSize(20);
    text->setFillColor(sf::Color::Black);

    endText = std::make_shared<sf::Text>(*font);
    endText->setCharacterSize(40);
    endText->setStyle(sf::Text::Bold);

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

            tile.setPosition({x, y});
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
                text->setString(std::string(1, info));
                text->setPosition({x + 8.f, y + 2.f});
                window.draw(*text);
            }
        }
    }

    if (board.getGameState() == FINISHED_WIN)
    {
        endText->setString("YOU WIN!");
        endText->setFillColor(sf::Color::Green);
        endText->setPosition({10.f, 10.f});
        window.draw(*endText);
    }
    else if (board.getGameState() == FINISHED_LOSS)
    {
        endText->setString("YOU LOSE!");
        endText->setFillColor(sf::Color::Red);
        endText->setPosition({10.f, 10.f});
        window.draw(*endText);
    }
}