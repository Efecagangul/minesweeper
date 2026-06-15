#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"
#include "MSSFMLView.h"

int main()
{
    MinesweeperBoard board(10, 10, EASY);
    MSSFMLView view(board);

    int windowWidth = board.getBoardWidth() * 32;
    int windowHeight = board.getBoardHeight() * 32;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        view.draw(window);
        window.display();
    }

    return 0;
}