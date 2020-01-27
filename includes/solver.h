#ifndef SOLVER_H
#define SOLVER_H
#include <vector>
#include "SDL.h"

extern SDL_Event event;

void maze_solver(std::vector<std::vector<int>>& maze, int maze_size, int zoom);

#endif