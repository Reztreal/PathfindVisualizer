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
            {
	            for (int i = 0; i < path_map.gridSize; i++)
	            {
		            for (int j = 0; j < path_map.gridSize; j++)
		            {
                        std::cout << path_map.GetCell(i, j).cellType << " ";
		            }
                    std::cout << "\n";
	            }
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
	            if (event.mouseButton.button == sf::Mouse::Left)
	            {
                    if (mousePos.x > 0 && mousePos.y > 0 && mousePos.x < 625 && mousePos.y < 625)
                    {
                        sf::Vector2f lastPos = startCell.cellRect.getPosition();
                        path_map.SetCellType(floor(lastPos.x / 25), floor(lastPos.y / 25), Cell::empty);

                    	startCell = path_map.SetCellType(floor(mousePos.x / 25), floor(mousePos.y / 25), Cell::start);
                        startCellPos = startCell.cellRect.getPosition();
                    }
	            }

                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if (mousePos.x > 0 && mousePos.y > 0 && mousePos.x < 625 && mousePos.y < 625)
                    {
                        sf::Vector2f lastPos = endCell.cellRect.getPosition();
                        path_map.SetCellType(floor(lastPos.x / 25), floor(lastPos.y / 25), Cell::empty);

                        endCell = path_map.SetCellType(floor(mousePos.x / 25), floor(mousePos.y / 25), Cell::end);
                        endCellPos = endCell.cellRect.getPosition();
                    }
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
	            if (event.key.code == sf::Keyboard::Space)
	            {
                    if (mousePos.x > 0 && mousePos.y > 0 && mousePos.x < 625 && mousePos.y < 625)
                    {
                        Cell cell = path_map.GetCell(mousePos.x / 25, mousePos.y / 25);
                        sf::Vector2f cellPos = cell.cellRect.getPosition();

                        if (cell.cellType == Cell::empty)
                        {
                            path_map.SetCellType(cellPos.x / 25, cellPos.y / 25, Cell::obstacle);
                        }
                        else if (cell.cellType == Cell::obstacle)
                        {
                            path_map.SetCellType(cellPos.x / 25, cellPos.y / 25, Cell::empty);
                        }
                    }
	            }

                if (event.key.code == sf::Keyboard::G)
                {
                    std::queue<Cell> fringe;
                    std::set<std::pair<int, int>> visitedCells;
                    fringe.push(startCell);
                    visitedCells.insert({ startCellPos.x / 25, startCellPos.y / 25 });
                    std::cout << "STARTING CELL X: " << startCellPos.x / 25 << " STARTING CELL Y: " << startCellPos.y / 25 << "\n";

                    while(!fringe.empty())
                    {
                        Cell& node = fringe.front();
                        sf::Vector2f nodePos = node.cellRect.getPosition();
                        int x = nodePos.x;
                        int y = nodePos.y;

                        path_map.SetCellType(nodePos.x / 25, nodePos.y / 25, Cell::visited);

                    	std::vector<sf::Vector2f> neighbors = PathMap::GetNeighborCells(node.cellRect);
                        for (auto& cell : neighbors)
                        {
                            int newX = cell.x / 25;
                            int newY = cell.y / 25;
                            Cell& neighbor = path_map.GetCell(newX, newY);
                            neighbor.previousCell = &node;

                            if (visitedCells.count({newX, newY}) == 0 && neighbor.cellType != Cell::obstacle)
                            {
                                fringe.push(path_map.GetCell(newX, newY));
                                visitedCells.insert({ newX, newY });
                                path_map.SetCellType(newX, newY, Cell::visited);
                            }
                        }
                        fringe.pop();
                    }

                    Cell* currentCell = &endCell;
                    while (currentCell != nullptr)
                    {
	                    std::cout << currentCell << "\n";
                        currentCell = currentCell->previousCell;
                    }
                }

                if (event.key.code == sf::Keyboard::M)
                {
                    std::vector<sf::Vector2f> neighbors = PathMap::GetNeighborCells(startCell.cellRect);
                    std::cout << "STARTING CELL X: " << startCellPos.x / 25 << " STARTING CELL Y: " << startCellPos.y / 25 << "\n";
                    for (auto cell : neighbors)
                    {
                        path_map.SetCellType(cell.x / 25, cell.y / 25, Cell::visiting);
	                    std::cout << "X: " << cell.x/25 << " Y: " << cell.y/25 << "\n";
                    }
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
        //std::cout << startCell.cellRect.getPosition().x << " " << startCell.cellRect.getPosition().y << "\n";

        window.display();
    }
    return 0;
}