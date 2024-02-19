#include <iostream>
#include "SFML/Graphics.hpp"
#include "PathMap.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Window Title");

    PathMap path_map;
    sf::Vector2i mousePos;
    Cell startCell;
    Cell endCell;
    sf::Vector2f startCellPos;
    sf::Vector2f endCellPos;


    sf::Clock deltaClock;
    while (window.isOpen())
    {
        mousePos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
	            if (event.mouseButton.button == sf::Mouse::Left)
	            {
                    if (mousePos.x > 0 && mousePos.y > 0 && mousePos.x < 625 && mousePos.y < 625)
                    {
                        sf::Vector2f lastPos = startCell.cellRect.getPosition();
                        path_map.SetCellType(lastPos.x / 25, lastPos.y / 25, Cell::empty);

                    	startCell = path_map.SetCellType(mousePos.x / 25, mousePos.y / 25, Cell::start);
                        startCellPos = startCell.cellRect.getPosition();
                    }
	            }

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if (mousePos.x > 0 && mousePos.y > 0 && mousePos.x < 625 && mousePos.y < 625)
                    {
                        sf::Vector2f lastPos = endCell.cellRect.getPosition();
                        path_map.SetCellType(lastPos.x / 25, lastPos.y / 25, Cell::empty);

                        endCell = path_map.SetCellType(mousePos.x / 25, mousePos.y / 25, Cell::end);
                        endCellPos = startCell.cellRect.getPosition();
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
	            if (event.key.code == sf::Keyboard::Space)
	            {
                    std::cout << "SPACE" << "\n";
	            }
            }
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

        

        //std::cout << "X: " << sf::Mouse::getPosition(window).x << " Y: " << sf::Mouse::getPosition(window).y << "\n";
        std::cout << startCell.cellRect.getPosition().x << " " << startCell.cellRect.getPosition().y << "\n";

        window.display();
    }
    return 0;
}