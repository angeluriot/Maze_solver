#ifndef GENERATOR_H
#define GENERATOR_H
#include <vector>
#include <SFML/Graphics.hpp>

bool is_finished(std::vector<std::vector<int>>& maze, int maze_size);
void create_grid(std::vector<std::vector<int>>& maze, int maze_size, int zoom);
void maze_generator(std::vector<std::vector<int>>& maze, int maze_size, bool is_complex, int zoom, sf::Event& sf_event, sf::RenderWindow& window, bool& end, sf::RectangleShape& pixel);

#endif