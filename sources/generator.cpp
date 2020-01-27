#include "generator.h"
#include "display.h"
#include "color.h"



// Vérifie si le labyrinthe est terminé

bool is_finished(std::vector<std::vector<int>>& maze, int maze_size)
{
	for (int i = 1; i < maze_size - 1; i += 2)
	{
		for (int j = 1; j < maze_size - 1; j += 2)
		{
			if (maze.at(i).at(j) != maze.at(1).at(1))
				return 0;
		}
	}

	return 1;
}



// Remplie le labyrinthe de telle sorte à ce que chaque case soit entourée par des murs

void create_grid(std::vector<std::vector<int>>& maze, int maze_size, int zoom)
{
	int nb = 0;
	std::vector<int> wall;
	std::vector<int> line;

	for (int i = 0; i < maze_size; i++)
	{
		wall.push_back(-1);

		if (i % 2 == 1)
			line.push_back(0);

		else
			line.push_back(-1);
	}

	for (int i = 0; i < maze_size; i++)
	{
		if (i % 2 == 0)
			maze.push_back(wall);

		else
			maze.push_back(line);
	}

	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			if (maze.at(i).at(j) == 0)
			{
				nb++;
				maze.at(i).at(j) = nb;
			}
		}
	}

	maze.at(1).at(0) = 1;
	maze.at(maze_size - 2).at(maze_size - 1) = nb;

	show_maze(maze, maze_size, zoom);
}



// Casse les murs jusqu'à ce que toutes les cases soient accessibles (Si "is_hard" = true, alors le labyrinthe sera complexe, sinon il sera simple)

void maze_generator(std::vector<std::vector<int>>& maze, int maze_size, bool is_complex, int zoom)
{
	while (is_finished(maze, maze_size) == 0)
	{
		int x = rand() % (maze_size - 2) + 1;
		int y;

		if (x % 2 == 0)
			y = ((rand() % ((maze_size - 1) / 2))) * 2 + 1;

		else
			y = ((rand() % ((maze_size - 2) / 2))) * 2 + 2;

		int cell_1;
		int cell_2;

		if (maze.at(x - 1).at(y) == -1)
		{
			cell_1 = maze.at(x).at(y - 1);
			cell_2 = maze.at(x).at(y + 1);
		}

		else
		{
			cell_1 = maze.at(x - 1).at(y);
			cell_2 = maze.at(x + 1).at(y);
		}

		if (cell_1 != cell_2)
		{
			maze.at(x).at(y) = 0;
			show_pixel(x, y, Color(255, 255, 255), zoom);

			for (int i = 1; i < maze_size - 1; i += 2)
			{
				for (int j = 1; j < maze_size - 1; j += 2)
				{
					if (maze.at(i).at(j) == cell_2)
						maze.at(i).at(j) = cell_1;
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

	if (is_complex) // rend le labyrinthe complexe
	{
		for (int i = 0; i < maze_size; i++)
		{
			int x = rand() % (maze_size - 2) + 1;
			int y;

			if (x % 2 == 0)
				y = ((rand() % ((maze_size - 1) / 2))) * 2 + 1;

			else
				y = ((rand() % ((maze_size - 2) / 2))) * 2 + 2;

			maze.at(x).at(y) = 0;
			show_pixel(x, y, Color(255, 255, 255), zoom);
		}
	}
}