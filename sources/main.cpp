#include "solver.h"
#include "generator.h"
#include "display.h"
#include "utils.h"
#include <SFML/Graphics.hpp>

int main()
{
	// Initialisation de la fenêtre en fonction de l'écran

	int	maze_size = 101;
	int width = (sf::VideoMode::getDesktopMode().height * 3) / 4;
	int zoom = (int)((double)width / (double)maze_size);
	width = zoom * maze_size;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(width + GAP * 2, width + GAP * 2), "Maze solver", sf::Style::Close | sf::Style::Titlebar, settings);

	sf::Image icon;
	icon.loadFromFile("dependencies/resources/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	bool is_complex = true;
	bool end = false;
	sf::Event sf_event;
	sf::RectangleShape pixel;
	pixel.setSize(sf::Vector2f(zoom, zoom));
	std::vector<std::vector<int>> maze;

	// lancement de la simulation

	while (window.isOpen() and !end)
	{
		events(sf_event, window, end);

		window.clear(sf::Color::White);

		maze_generator(maze, maze_size, is_complex, zoom, sf_event, window, end, pixel);
		maze_solver(maze, maze_size, zoom, sf_event, window, end, pixel);

		sf::sleep(sf::seconds(1));
		maze.clear();
	}

	return 0;
}