#pragma once
#include "Cell.h"

class PathMap
{
public:
	PathMap()
	{
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				grid[i][j].cellRect = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
				grid[i][j].cellRect.setPosition(i * (cellSize + gapSize) + gapSize, j * (cellSize + gapSize) + gapSize);
				grid[i][j].cellType = Cell::empty;
				grid[i][j].SetType();
			}
		}
	}

	Cell& GetCell(int x, int y)
	{
		if (x >= 0 && x <= 625 && y >= 0 && y <= 625)
		{
			int nX = x / (cellSize + gapSize);
			int nY = y / (cellSize + gapSize);
			return grid[nX][nY];
		}
	}

	void Draw(sf::RenderWindow& window) const
	{
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				window.draw(grid[i][j].cellRect);
			}
		}
	}

	std::vector<sf::Vector2i> GetNeighbors(sf::Vector2i pos)
	{
		std::vector<sf::Vector2i> neighbors;

		//std::cout << "POSX: " << pos.x / 25 << " POSY: " << pos.y / 25 << "\n";

		std::vector<std::pair<int, int>> directions =
		{
			{0, -25},
			{25, 0},
			{0, 25},
			{-25, 0}
		};


		for (auto& dir : directions)
		{
			int newX = pos.x + dir.first;
			int newY = pos.y + dir.second;

			if (newX >= 0 && newX <= 625 && newY >= 0 && newY <= 625)
			{
				neighbors.push_back(sf::Vector2i(newX, newY));
			}
		}

		return neighbors;
	}

	void BFSStep(std::queue<sf::Vector2i>& bfsQueue)
	{
		if (!bfsQueue.empty() && !bfsComplete)
		{
			sf::Vector2i node = bfsQueue.front();
			int nodeX = node.x / 25;
			int nodeY = node.y / 25;
			bfsQueue.pop();

			grid[nodeX][nodeY].cellType = Cell::visited;
			//grid[nodeX][nodeY].SetType();

			std::vector<sf::Vector2i> neighbors = GetNeighbors(node);
			for (auto& neighbor : neighbors)
			{
				if (grid[neighbor.x / 25][neighbor.y / 25].cellType == Cell::end)
				{
					bfsComplete = true;
					std::cout << "END CELL FOUND\n";
					std::cout << "X: " << neighbor.x / 25 << " Y: " << neighbor.y / 25 << "\n";

					Cell* tmp = &grid[node.x / 25][node.y / 25];

					if (tmp->prevCell != nullptr)
					{
						while (tmp->prevCell != nullptr)
						{
							tmp->cellRect.setFillColor(sf::Color::Yellow);
							tmp = tmp->prevCell;
						}
					}

					return;
				}
				if (grid[neighbor.x / 25][neighbor.y / 25].cellType != Cell::visited && grid[neighbor.x / 25][neighbor.y / 25].cellType != Cell::obstacle)
				{
					grid[neighbor.x / 25][neighbor.y / 25].cellType = Cell::visited;
					grid[neighbor.x / 25][neighbor.y / 25].prevCell = &grid[nodeX][nodeY];
					grid[neighbor.x / 25][neighbor.y / 25].SetType();
					bfsQueue.push(neighbor);
				}
			}
		}
	}

public:
	static constexpr int gridSize = 25;
	static constexpr int cellSize = 20;

	static constexpr int gapSize = 5;
	bool bfsComplete = false;

	Cell grid[gridSize][gridSize];
};

