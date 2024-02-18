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



public:
	static constexpr int gridSize = 25;
	static constexpr int cellSize = 20;
	Cell* grid;
};

