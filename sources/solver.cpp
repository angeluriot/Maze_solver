#include "solver.h"
#include "display.h"
#include "utils.h"


void score_boxes(std::vector<std::vector<int>>& maze, int maze_size, int zoom, sf::Event& sf_event, sf::RenderWindow& window, bool& end, sf::RectangleShape& pixel)
{
	maze[1][0] = 0;

	for (int i = 1; i < maze_size - 1; i++)
	{
		for (int j = 1; j < maze_size - 1; j++)
		{
			if (maze[i][j] >= 0)
				maze[i][j] = 0;
		}
	}

	int distance = 1;
	std::vector<std::vector<int>> temp;

	maze[maze_size - 2][maze_size - 1] = 1;
	show_pixel(maze_size - 2, maze_size - 1, sf::Color(255, 255, 0), zoom, pixel, window);

	while (maze[1][1] == 0) // Donne à chaque case la distance entre sa position et la sortie (ainsi qu'une couleur correspondante)
	{
		temp = maze;
		distance++;

		for (int i = maze_size - 2; i > 0; i--)
		{
			for (int j = maze_size - 2; j > 0; j--)
			{
				if (maze[i][j] == 0)
				{
					if (maze[i - 1][j] > 0 or maze[i + 1][j] > 0 or maze[i][j - 1] > 0 or maze[i][j + 1] > 0)
					{
						temp[i][j] = distance;
						show_pixel(i, j, color(distance, maze_size * 1.5), zoom, pixel, window);
					}
				}
			}

			events(sf_event, window, end);
		}

		maze = temp;
	}

	maze[1][0] = distance + 20;

	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			if (maze[i][j] == 0)
				maze[i][j] = distance + 1;

			if (maze[i][j] == -1)
				maze[i][j] = distance + 10;
		}
	}
}



// Résout le labyrinthe

void maze_solver(std::vector<std::vector<int>>& maze, int maze_size, int zoom, sf::Event& sf_event, sf::RenderWindow& window, bool& end, sf::RectangleShape& pixel)
{
	score_boxes(maze, maze_size, zoom, sf_event, window, end, pixel);

	show_pixel(1, 0, sf::Color(0, 255, 0), zoom, pixel, window);
	show_pixel(1, 1, sf::Color(0, 255, 0), zoom, pixel, window);

	int x = 1;
	int y = 1;

	int up, down, left, right;

	while (x != maze_size - 2 or y != maze_size - 2) // Trace le chemin vert (le chemin le plus court entre l'entrée et la sortie)
	{
		up = maze[x][y - 1];
		down = maze[x][y + 1];;
		left = maze[x - 1][y];;
		right = maze[x + 1][y];;

		if (up <= down and up <= left and up <= right)
			y = y - 1;

		else if (down <= up and down <= left and down <= right)
			y = y + 1;

		else if (left <= up and left <= down and left <= right)
			x = x - 1;

		else if (right <= up and right <= down and right <= left)
			x = x + 1;

		show_pixel(x, y, sf::Color(0, 255, 0), zoom, pixel, window);

		events(sf_event, window, end);
	}

	show_pixel(maze_size - 2, maze_size - 1, sf::Color(0, 255, 0), zoom, pixel, window);
}