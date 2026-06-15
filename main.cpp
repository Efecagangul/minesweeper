#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"
#include "MSSFMLView.h"
#include "MSSFMLController.h"

int main()
{
    MinesweeperBoard board(20, 15, NORMAL);
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