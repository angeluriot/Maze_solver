#ifndef SOLVER_H
#define SOLVER_H
#include <vector>
#include <SFML/Graphics.hpp>

void score_boxes(std::vector<std::vector<int>>& maze, int maze_size, int zoom, sf::Event& sf_event, sf::RenderWindow& window, bool& end, sf::RectangleShape& pixel);
void maze_solver(std::vector<std::vector<int>>& maze, int maze_size, int zoom, sf::Event& sf_event, sf::RenderWindow& window, bool& end, sf::RectangleShape& pixel);

#endif