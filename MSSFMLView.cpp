#include "MSSFMLView.h"
#include <iostream>

MSSFMLView::MSSFMLView(MinesweeperBoard& board) : board(board)
{
    font = std::make_shared<sf::Font>();
    fontLoaded = false;
    if (font->loadFromFile("arial.ttf"))
    {
        fontLoaded = true;
    }
    else if (font->loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
    {
        fontLoaded = true;
    }
    else
    {
        std::cerr << "Warning: Could not load arial.ttf or DejaVuSans.ttf; numbers will use fallback drawing.\n";
    }

    text = std::make_shared<sf::Text>();
    text->setFont(*font);
    text->setCharacterSize(20);
    text->setFillColor(sf::Color::Black);

    endText = std::make_shared<sf::Text>();
    endText->setFont(*font);
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
                if (fontLoaded)
                {
                    text->setString(std::string(1, info));
                    text->setPosition({x + 8.f, y + 2.f});
                    window.draw(*text);
                }
                else
                {
                    // Fallback: draw a small colored square for non-zero counts
                    int count = info - '0';
                    sf::RectangleShape mark(sf::Vector2f(12.f, 12.f));
                    mark.setPosition({x + 10.f, y + 10.f});
                    // color map for counts
                    static const sf::Color colors[] = {
                        sf::Color::White,
                        sf::Color(0,0,255), // 1 - blue
                        sf::Color(0,128,0), // 2 - green
                        sf::Color(255,0,0), // 3 - red
                        sf::Color(128,0,128), // 4 - purple
                        sf::Color(128,0,0), // 5 - maroon
                        sf::Color(64,224,208), // 6 - turquoise
                        sf::Color(0,0,0), // 7 - black
                        sf::Color(128,128,128) // 8 - gray
                    };
                    sf::Color col = (count >=1 && count <=8) ? colors[count] : sf::Color::Black;
                    mark.setFillColor(col);
                    window.draw(mark);
                }
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