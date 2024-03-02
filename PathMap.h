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
				grid[index].SetType();
			}
		}
	}

	sf::RectangleShape& GetCellRect(int x, int y) const
	{
		return grid[x * gridSize + y].cellRect;
	}

	Cell& GetCell(int x, int y) 
	{
		if (x >= 0 && x <= 625 && y >= 0 && y <= 625 )
			return grid[x * gridSize + y];
	}



	Cell& SetCellType(int x, int y, Cell::Type type)
	{
		Cell& cell = GetCell(x, y);
		cell.cellType = type;
		cell.SetType();

		return cell;
	}

	static std::vector<sf::Vector2f> GetNeighborCells(const sf::RectangleShape rect)
	{
		std::vector<sf::Vector2f> neighborVec;
		sf::Vector2f currentPos = rect.getPosition();

		std::vector<std::pair<int, int>> directions = {
			{0, -25},
			{25, 0},
			{0, 25},
			{-25, 0}
		};

		for (const auto& dir : directions)
		{
			int newX = rect.getPosition().x + dir.first;
			int newY = rect.getPosition().y + dir.second;

			if (newX >= 0 && newX <= 625 && newY >= 0 && newY <= 625)
			{
				neighborVec.push_back(sf::Vector2f(newX, newY));
			}
		}

		return neighborVec;
	}



public:
	static constexpr int gridSize = 25;
	static constexpr int cellSize = 20;
	Cell* grid;
};

