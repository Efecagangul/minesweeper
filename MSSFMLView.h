#pragma once
#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"
#include <memory>

class MSSFMLView
{
    MinesweeperBoard& board;
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<sf::Text> text;
    std::shared_ptr<sf::Text> endText;
    sf::RectangleShape tile;
    bool fontLoaded;

public:
    explicit MSSFMLView(MinesweeperBoard& board);
    void draw(sf::RenderWindow& window);
};