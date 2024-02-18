#pragma once

class Cell
{
public:
	enum Type;

	void SetColor()
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

		case end:
			cellRect.setFillColor(endColor);
			break;
		}
		
	}


public:
	enum Type { empty, obstacle, start, end };
	Type cellType = empty;

	sf::RectangleShape cellRect;
	sf::Color emptyColor = sf::Color(232, 249, 253);
	sf::Color obstacleColor = sf::Color(34, 9, 44);
	sf::Color startColor = sf::Color(89, 206, 143);
	sf::Color endColor = sf::Color(255, 30, 0);
};
