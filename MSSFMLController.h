#pragma once
#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"

class MSSFMLController
{
    MinesweeperBoard& board;

public:
    explicit MSSFMLController(MinesweeperBoard& board);
    void handleEvent(sf::Event& event);
};