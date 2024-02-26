#pragma once
#include "Cell.h"

class PathMap
{
public:
	PathMap()
	{
		grid = new Cell[gridSize * gridSize];
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				int index = i * gridSize + j;
				grid[index].cellRect = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
				grid[index].cellType = Cell::empty;
				grid[index].SetColor();
			}
		}
	}

	sf::RectangleShape& GetCellRect(int x, int y) const
	{
		return grid[x * gridSize + y].cellRect;
	}

	Cell& GetCell(int x, int y) const
	{
		return grid[x * gridSize + y];
	}

	Cell& SetCellType(int x, int y, Cell::Type type)
	{
		Cell& cell = GetCell(x, y);
		cell.cellType = type;
		cell.SetColor();

		return cell;
	}

	static std::vector<sf::Vector2f> GetNeighborCells(const sf::RectangleShape rect)
	{
		std::vector<sf::Vector2f> neighborVec;
		sf::Vector2f currentPos = rect.getPosition();

		sf::Vector2f up = sf::Vector2f(currentPos.x , currentPos.y - 25);
		sf::Vector2f right = sf::Vector2f(currentPos.x + 25, currentPos.y);
		sf::Vector2f down = sf::Vector2f(currentPos.x, currentPos.y + 25);
		sf::Vector2f left = sf::Vector2f(currentPos.x - 25, currentPos.y);

		// Add these to the vec with an if condition to check neighbor cells are inside the grid

		neighborVec.push_back(up);
		neighborVec.push_back(right);
		neighborVec.push_back(down);
		neighborVec.push_back(left);

		return neighborVec;
	}



public:
	static constexpr int gridSize = 25;
	static constexpr int cellSize = 20;
	Cell* grid;
};

