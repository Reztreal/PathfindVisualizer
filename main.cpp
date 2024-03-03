#include <iostream>
#include <queue>
#include <set>
#include <chrono>
#include <thread>

#include "SFML/Graphics.hpp"
#include "PathMap.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Window Title");

    PathMap path_map;
    sf::Vector2i startCellPos = sf::Vector2i(-1, -1);
    sf::Vector2i endCellPos = sf::Vector2i(-1, -1);

    std::queue<sf::Vector2i> bfsq;



    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
	            for (int i = 0; i < path_map.gridSize; i++)
	            {
		            for (int j = 0; j < path_map.gridSize; j++)
		            {
                        std::cout << path_map.GetCell(i * 25, j * 25).cellType << " ";
		            }
                    std::cout << "\n";
	            }
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            	std::cout << "X,Y " << mousePos.x << " " << mousePos.y << "\n";

                if (mousePos.x >= 0 && mousePos.x <= 625 && mousePos.y >= 0 && mousePos.y <= 625)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        Cell& cell = path_map.GetCell(mousePos.x, mousePos.y);
                        if (startCellPos.x != -1 && startCellPos.y != -1)
                        {
                            Cell& prevCell = path_map.GetCell(startCellPos.x, startCellPos.y);
                            prevCell.cellType = Cell::empty;
                            prevCell.SetType();
                        }

                        startCellPos.x = mousePos.x;
                        startCellPos.y = mousePos.y;
                        cell.cellType = Cell::start;
                        cell.SetType();
                        bfsq.push(startCellPos);
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        Cell& cell = path_map.GetCell(mousePos.x, mousePos.y);
                        if (endCellPos.x != -1 && endCellPos.y != -1)
                        {
                            Cell& prevCell = path_map.GetCell(endCellPos.x, endCellPos.y);
                            prevCell.cellType = Cell::empty;
                            prevCell.SetType();
                        }

                        endCellPos.x = mousePos.x;
                        endCellPos.y = mousePos.y;
                        cell.cellType = Cell::end;
                        cell.SetType();
                    }
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
	            if (event.key.code == sf::Keyboard::Space)
	            {
                    path_map.BFSStep(bfsq);
	            }
            }
        }
        window.clear(sf::Color(18, 33, 43));

        path_map.Draw(window);

        window.display();
    }
    return 0;
}