#pragma once

class Cell
{
public:
	enum Type;

	void SetType()
	{
		switch (cellType)
		{
		case empty:
			cellRect.setFillColor(emptyColor);
			break;

		case obstacle:
			cellRect.setFillColor(obstacleColor);
			break;

		case start:
			cellRect.setFillColor(startColor);
			break;

		case visiting:
			cellRect.setFillColor(visitingColor);
			break;

		case visited:
			cellRect.setFillColor(visitedColor);
			break;

		case end:
			cellRect.setFillColor(endColor);
			break;
		}
		
	}

	void SetColor(sf::Color c)
	{
		cellRect.setFillColor(c);
	}


public:
	enum Type { empty, obstacle, start, visiting, visited, end };
	Type cellType = empty;

	Cell* prevCell = nullptr;

	sf::RectangleShape cellRect;
	sf::Color emptyColor = sf::Color(232, 249, 253);
	sf::Color obstacleColor = sf::Color(34, 9, 44);
	sf::Color startColor = sf::Color(89, 206, 143);
	sf::Color endColor = sf::Color(255, 30, 0);
	sf::Color visitedColor = sf::Color(38, 80, 115);
	sf::Color visitingColor = sf::Color(154, 208, 194);
};
