#ifndef DISPLAY_H
#define DISPLAY_H
#include <vector>
#include <SFML/Graphics.hpp>

#define GAP 20 // Distance entre les bords de la fenêtre et le labyrinthe

sf::Color color(int value, const int& max_value);
void show_pixel(int x, int y, const sf::Color& color, int zoom, sf::RectangleShape& pixel, sf::RenderWindow& window);
void show_maze(std::vector<std::vector<int>>& maze, int maze_size, int zoom, sf::RectangleShape& pixel, sf::RenderWindow& window);

#endif