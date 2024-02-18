#include <iostream>
#include "SFML/Graphics.hpp"
#include "PathMap.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Window Title");

    PathMap path_map;

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(18, 33, 43));

        for (int i = 0; i < path_map.gridSize; i++)
        {
	        for (int j = 0; j < path_map.gridSize; j++)
	        {
                sf::RectangleShape& cell = path_map.GetCellRect(i, j);
                cell.setPosition(i * (PathMap::cellSize + 5) + 5, j * (PathMap::cellSize + 5) + 5);
                window.draw(cell);
	        }
        }
        
        path_map.SetCellType(0, 0, Cell::end);

        window.display();
    }
    return 0;
}