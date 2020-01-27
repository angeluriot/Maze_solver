#ifndef DISPLAY_H
#define DISPLAY_H
#include "color.h"
#include <vector>
#include "SDL.h"

#define GAP 20 // Distance entre les bords de la fenêtre et le labyrinthe

extern SDL_Renderer* renderer;

void show_pixel(int x, int y, const Color& color, int zoom);
void show_maze(std::vector<std::vector<int>>& maze, int maze_size, int zoom);

#endif