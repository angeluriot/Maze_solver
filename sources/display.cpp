#include "display.h"



// Affiche une case du labyrinthe

void show_pixel(int x, int y, const Color& color, int zoom)
{
	x = GAP + zoom * x;
	y = GAP + zoom * y;

	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, SDL_ALPHA_OPAQUE);

	SDL_Rect rectangle[1];

	rectangle[0].h = zoom;
	rectangle[0].w = zoom;
	rectangle[0].x = y;
	rectangle[0].y = x;

	SDL_RenderFillRect(renderer, rectangle);
	SDL_RenderPresent(renderer);
}



// Affiche tout le labyrinthe

void show_maze(std::vector<std::vector<int>>& maze, int maze_size, int zoom)
{
	int x;
	int y;

	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			if (maze.at(i).at(j) == -1)
			{
				x = GAP + zoom * i;
				y = GAP + zoom * j;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

				SDL_Rect rectangle[1];

				rectangle[0].h = zoom;
				rectangle[0].w = zoom;
				rectangle[0].x = y;
				rectangle[0].y = x;

				SDL_RenderFillRect(renderer, rectangle);
			}
		}
	}

	SDL_RenderPresent(renderer);
}