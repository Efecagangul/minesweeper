#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"
#include "MSSFMLView.h"
#include "MSSFMLController.h"
#include <iostream>

static GameMode chooseModeFromInput(int v)
{
    switch (v)
    {
        case 0: return DEBUG;
        case 1: return EASY;
        case 2: return NORMAL;
        case 3: return HARD;
        default: return NORMAL;
    }
}

int main()
{
    int width = 20;
    int height = 15;
    int modeChoice = 2; // default NORMAL

    std::cout << "Enter board width (1-100) [20]: ";
    if (!(std::cin >> width)) { std::cin.clear(); width = 20; }
    if (width < 1 || width > 100) width = 20;

    std::cout << "Enter board height (1-100) [15]: ";
    if (!(std::cin >> height)) { std::cin.clear(); height = 15; }
    if (height < 1 || height > 100) height = 15;

    std::cout << "Choose mode: 0=DEBUG 1=EASY 2=NORMAL 3=HARD [2]: ";
    if (!(std::cin >> modeChoice)) { std::cin.clear(); modeChoice = 2; }

    GameMode mode = chooseModeFromInput(modeChoice);

    MinesweeperBoard board(width, height, mode);
    MSSFMLView view(board);
    MSSFMLController ctrl(board);

    unsigned int windowWidth = board.getBoardWidth() * 32;
    unsigned int windowHeight = board.getBoardHeight() * 32;

    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Minesweeper");
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            ctrl.handleEvent(event);
        }

        window.clear(sf::Color::Black);
        view.draw(window);
        window.display();
    }

    return 0;
}