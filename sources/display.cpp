#include "display.h"
#include "utils.h"



// Affiche une case du labyrinthe

void show_pixel(int x, int y, const sf::Color& color, int zoom, sf::RectangleShape& pixel, sf::RenderWindow& window)
{
	pixel.setPosition(sf::Vector2f(GAP + zoom * y, GAP + zoom * x));
	pixel.setFillColor(color);
	window.draw(pixel);
	window.display();
}



// Affiche tout le labyrinthe

void show_maze(std::vector<std::vector<int>>& maze, int maze_size, int zoom, sf::RectangleShape& pixel, sf::RenderWindow& window)
{
	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			if (maze[i][j] == -1)
			{
				pixel.setPosition(sf::Vector2f(GAP + zoom * j, GAP + zoom * i));
				pixel.setFillColor(sf::Color::Black);
				window.draw(pixel);
			}
		}
	}

	window.display();
}



// Donne une couleur à partir de la distance entre une case et la sortie

sf::Color color(int value, const int& max_value)
{
	value = int(double((double(value) / double(max_value)) * double(255)));

	if (value <= 255)
		return sf::Color(255, 255 - value, 0);

	if (value > 255 and value <= 255 * 2)
		return sf::Color(2 * 255 - value, 0, value - 255);

	if (value > 255 * 2 and value <= 255 * 3)
		return sf::Color(0, 0, 255 * 3 - value);

	return sf::Color(0, 0, 0);
}