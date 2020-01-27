#include "solver.h"
#include "display.h"
#include "color.h"



// Résout le labyrinthe

void maze_solver(std::vector<std::vector<int>>& maze, int maze_size, int zoom)
{
	maze.at(1).at(0) = 0;

	for (int i = 1; i < maze_size - 1; i++)
	{
		for (int j = 1; j < maze_size - 1; j++)
		{
			if (maze.at(i).at(j) >= 0)
				maze.at(i).at(j) = 0;
		}
	}

	int distance = 1;
	std::vector<std::vector<int>> temp;

	maze.at(maze_size - 2).at(maze_size - 1) = 1;
	show_pixel(maze_size - 2, maze_size - 1, Color(255, 255, 0), zoom);

	while (maze.at(1).at(1) == 0) // Donne à chaque case la distance entre sa position et la sortie (ainsi qu'une couleur correspondante)
	{
		temp = maze;
		distance++;

		for (int i = maze_size - 2; i > 0; i--)
		{
			for (int j = maze_size - 2; j > 0; j--)
			{
				if (maze.at(i).at(j) == 0)
				{
					if (maze.at(i - 1).at(j) > 0 or maze.at(i + 1).at(j) > 0 or maze.at(i).at(j - 1) > 0 or maze.at(i).at(j + 1) > 0)
					{
						temp.at(i).at(j) = distance;
						show_pixel(i, j, color(distance, maze_size * 1.5), zoom);
					}
				}
			}

			SDL_PollEvent(&event);

			if (event.type == SDL_QUIT)
			{
				SDL_Quit();
				exit(1);
			}
		}

		maze = temp;
	}

	maze.at(1).at(0) = distance + 20;

	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			if (maze.at(i).at(j) == 0)
				maze.at(i).at(j) = distance + 1;

			if (maze.at(i).at(j) == -1)
				maze.at(i).at(j) = distance + 10;
		}
	}

	show_pixel(1, 0, Color(0, 255, 0), zoom);
	show_pixel(1, 1, Color(0, 255, 0), zoom);

	int x = 1;
	int y = 1;

	while (x != maze_size - 2 or y != maze_size - 2) // Trace le chemin vert (le chemin le plus court entre l'entrée et la sortie)
	{
		if (maze.at(x).at(y - 1) <= maze.at(x).at(y + 1) and maze.at(x).at(y - 1) <= maze.at(x - 1).at(y) and maze.at(x).at(y - 1) <= maze.at(x + 1).at(y))
			y = y - 1;

		else if (maze.at(x).at(y + 1) <= maze.at(x).at(y - 1) and maze.at(x).at(y + 1) <= maze.at(x - 1).at(y) and maze.at(x).at(y + 1) <= maze.at(x + 1).at(y))
			y = y + 1;

		else if (maze.at(x - 1).at(y) <= maze.at(x).at(y - 1) and maze.at(x - 1).at(y) <= maze.at(x).at(y + 1) and maze.at(x - 1).at(y) <= maze.at(x + 1).at(y))
			x = x - 1;

		else if (maze.at(x + 1).at(y) <= maze.at(x).at(y - 1) and maze.at(x + 1).at(y) <= maze.at(x).at(y + 1) and maze.at(x + 1).at(y) <= maze.at(x - 1).at(y))
			x = x + 1;

		show_pixel(x, y, Color(0, 255, 0), zoom);

		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
		{
			SDL_Quit();
			exit(1);
		}
	}

	show_pixel(maze_size - 2, maze_size - 1, Color(0, 255, 0), zoom);
}