#include "solver.h"
#include "generator.h"
#include "display.h"
#include "color.h"
#include <vector>
#include <Windows.h>
#include "SDL.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;

int main(int argc, char* argv[])
{


	// ---------- Choix de l'utilisateur ----------



	int		zoom = 10;				// Taille des cases (en pixels)

	int		maze_size = 101;		// Taille du labyrinthe (en cases)
	bool	is_complex = true;		// Choisir si le labyrinthe sera complexe ou non

	int		nb_simulation = 100;	// Nombre de simulations



	// ---------- Lancement du programme ----------



	if (maze_size < 6) maze_size = 6;
	if (maze_size % 2 == 0) maze_size ++;
	if (zoom == 0) zoom = 1;
	if (nb_simulation < 1) nb_simulation = 1;

	SDL_Init(SDL_INIT_VIDEO);

	window = NULL;
	renderer = NULL;

	SDL_CreateWindowAndRenderer(maze_size * zoom + 2 * GAP, maze_size * zoom + 2 * GAP, 0, &window, &renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetWindowTitle(window, "Maze Solver");

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	std::vector<std::vector<int>> maze;

	for (int simu = 0; simu < nb_simulation; simu++)
	{
		create_grid(maze, maze_size, zoom);
		show_maze(maze, maze_size, zoom);
		maze_generator(maze, maze_size, is_complex, zoom);

		maze_solver(maze, maze_size, zoom);

		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
		{
			SDL_Quit();
			exit(1);
		}

		Sleep(1000);

		maze.clear();

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
	}

	if (renderer)
		SDL_DestroyRenderer(renderer);

	if (window)
		SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}