#include <windows.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <iomanip>



// ---------- Affichage ----------



HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

std::vector<std::vector<int>> maze; // Structure définissant le labyrinthe

int maze_size = 101; // Taille du labyrinthe

int zoom = 7; // Taille des cases en pixel

int screen_x = maze_size * zoom;
int screen_y = maze_size * zoom;

int gap_x = 200; // Décalage en X
int gap_y = 100; // Décalage en Y



// Affiche une case du labyrinthe

void set_point(int y, int x, const COLORREF &color)
{
	if (x >= 0 and x <= screen_x and y >= 0 and y <= screen_y)
	{
		x = gap_x + zoom * x;
		y = gap_y + zoom * y;

		for (int i = 0; i < zoom; i++)
		{
			for (int j = 0; j < zoom; j++)
				SetPixel(mydc, x + i, y + j, color);
		}
	}
}



// Affiche tout le labyrinthe

void show()
{
	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j ++)
		{
			if (maze.at(i).at(j) == -1)
				set_point(i, j, RGB(255, 255, 255));
		}
	}
}



// Fonction permettant de choisir la taille du labyrinthe dans le main

void set_size(int size)
{
	if (size < 6)
		size = 6;

	if (size % 2 == 0)
		size += 1;

	maze_size = size;

	zoom = 700 / maze_size;

	if (zoom == 0)
		zoom = 1;
}



// ---------- Génération du labyrinthe ----------



// Vérifie si le labyrinthe est terminé

bool is_finished()
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

void create_grid()
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
}



// Casse les murs jusqu'à ce que toutes les cases soient accessibles
// (Si "is_hard" = true, alors le labyrinthe sera complexe, sinon il sera simple)

void maze_generator(const bool &is_complex)
{
	while (is_finished() == 0)
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
			set_point(x, y, RGB(0, 0, 0));

			for (int i = 1; i < maze_size - 1; i += 2)
			{
				for (int j = 1; j < maze_size - 1; j += 2)
				{
					if (maze.at(i).at(j) == cell_2)
						maze.at(i).at(j) = cell_1;
				}
			}
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
			set_point(x, y, RGB(0, 0, 0));
		}
	}
}



// ---------- Résolution du labyrinthe ----------



// Donne une couleur à partir de la distance entre une case et la sortie

COLORREF color(int value, const int &max_value)
{
	value = int(double((double(value) / double(max_value)) * double(255)));

	if (value <= 255)
		return RGB(255, 255 - value, 0);

	if (value > 255 and value <= 255 * 2)
		return RGB(2 * 255 - value, 0, value - 255);

	if (value > 255 * 2 and value <= 255 * 3)
		return RGB(0, 0, (255 * 3 - value));

	return RGB(0, 0, 0);
}



// Résout le labyrinthe

void maze_solver()
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
	set_point(maze_size - 2, maze_size - 1, RGB(255, 255, 0));

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
						set_point(i, j, color(distance, maze_size * 1.5));
					}
				}
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

	set_point(1, 0, RGB(0, 255, 0));
	set_point(1, 1, RGB(0, 255, 0));

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

		set_point(x, y, RGB(0, 255, 0));
	}

	set_point(maze_size - 2, maze_size - 1, RGB(0, 255, 0));
}



// ---------- Le main ----------



int main()
{
	// ---------- Choix de l'utilisateur ----------



	set_size(100);           // Choisir la taille du labyrinthe
	bool is_complex = true;  // Choisir si le labyrinthe sera complexe ou non

	int nb_simulation = 100; // Choisir le nombre de simulations



	// ---------- Lancement du programme ----------



	MoveWindow(myconsole, 0, 0, 1920, 1080, TRUE);
	Sleep(100);

	for (int simu = 0; simu < nb_simulation; simu++)
	{
		create_grid();
		show();

		maze_generator(is_complex);

		maze_solver();

		Sleep(1000);
		maze.clear();
		system("cls");
		Sleep(100);
	}

	return 0;
}