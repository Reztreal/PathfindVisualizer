#include <iostream>
#include <queue>

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
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time interval = sf::milliseconds(10);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            	std::cout << "X,Y " << mousePos.x / 25 << " " << mousePos.y / 25 << "\n";

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

                if (event.key.code == sf::Keyboard::M)
                {
                    Cell& cell = path_map.GetCell(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                    cell.cellType = Cell::obstacle;
                    cell.SetType();
                }
            }
        }


        timeSinceLastUpdate += deltaClock.restart();
        while (timeSinceLastUpdate > interval)
        {
            if (!bfsq.empty())
            {
                path_map.BFSStep(bfsq);
            }
            timeSinceLastUpdate -= interval;
        }


        window.clear(sf::Color(18, 33, 43));

        path_map.Draw(window);

        window.display();
    }
    return 0;
}