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

int size = 101; // Taille du labyrinthe

int zoom = 7; // Taille des cases en pixel

int ScreenX = size * zoom;
int ScreenY = size * zoom;

int GapX = 200; // Décalage en X
int GapY = 100; // Décalage en Y



// Affiche une case du labyrinthe

void set_point(int y, int x, COLORREF color)
{
	if (x >= 0 and x <= ScreenX and y >= 0 and y <= ScreenY)
	{
		x = GapX + zoom * x;
		y = GapY + zoom * y;

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
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j ++)
		{
			if (maze.at(i).at(j) == -1)
				set_point(i, j, RGB(255, 255, 255));
		}
	}
}



// Fonction permettant de choisir la taille du labyrinthe dans le main

void set_size(int s)
{
	if (s < 6)
		s = 6;

	if (s % 2 == 0)
		s += 1;

	size = s;

	zoom = 700 / size;

	if (zoom == 0)
		zoom = 1;
}



// ---------- Génération du labyrinthe ----------



// Vérifie si le labyrinthe est terminé

bool is_finished()
{
	for (int i = 1; i < size - 1; i += 2)
	{
		for (int j = 1; j < size - 1; j += 2)
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

	for (int i = 0; i < size; i++)
	{
		wall.push_back(-1);

		if (i % 2 == 1)
			line.push_back(0);

		else
			line.push_back(-1);
	}

	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0)
			maze.push_back(wall);

		else
			maze.push_back(line);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (maze.at(i).at(j) == 0)
			{
				nb++;
				maze.at(i).at(j) = nb;
			}
		}
	}

	maze.at(1).at(0) = 1;
	maze.at(size - 2).at(size - 1) = nb;
}



// Casse les murs jusqu'à ce que toutes les cases soient accessibles
// (Si "is_hard" = 1, alors le labyrinthe sera complexe, sinon il sera simple)

void maze_generator(bool is_hard)
{
	while (is_finished() == 0)
	{
		int i = rand() % (size - 2) + 1;
		int j;

		if (i % 2 == 0)
			j = ((rand() % ((size - 1) / 2))) * 2 + 1;

		else
			j = ((rand() % ((size - 2) / 2))) * 2 + 2;

		int cell_1;
		int cell_2;

		if (maze.at(i - 1).at(j) == -1)
		{
			cell_1 = maze.at(i).at(j - 1);
			cell_2 = maze.at(i).at(j + 1);
		}

		else
		{
			cell_1 = maze.at(i - 1).at(j);
			cell_2 = maze.at(i + 1).at(j);
		}

		if (cell_1 != cell_2)
		{
			maze.at(i).at(j) = 0;
			set_point(i, j, RGB(0, 0, 0));

			for (int k = 1; k < size - 1; k += 2)
			{
				for (int l = 1; l < size - 1; l += 2)
				{
					if (maze.at(k).at(l) == cell_2)
						maze.at(k).at(l) = cell_1;
				}
			}
		}
	}

	if (is_hard) // rend le labyrinthe complexe
	{
		for (int k = 0; k < size; k++)
		{
			int i = rand() % (size - 2) + 1;
			int j;

			if (i % 2 == 0)
				j = ((rand() % ((size - 1) / 2))) * 2 + 1;

			else
				j = ((rand() % ((size - 2) / 2))) * 2 + 2;

			maze.at(i).at(j) = 0;
			set_point(i, j, RGB(0, 0, 0));
		}
	}
}



// ---------- Résolution du labyrinthe ----------



// Donne une couleur à partir de la distance entre une case et la sortie

COLORREF color(int d, int max)
{
	d = int(double((double(d) / double(max)) * double(255)));

	if (d <= 255)
		return RGB(255, 255 - d, 0);

	if (d > 255 and d <= 255 * 2)
		return RGB(2 * 255 - d, 0, d - 255);

	if (d > 255 * 2 and d <= 255 * 3)
		return RGB(0, 0, (255 * 3 - d));

	return RGB(0, 0, 0);
}



// Résout le labyrinthe

void maze_solver()
{
	maze.at(1).at(0) = 0;

	for (int i = 1; i < size - 1; i++)
	{
		for (int j = 1; j < size - 1; j++)
		{
			if (maze.at(i).at(j) >= 0)
				maze.at(i).at(j) = 0;
		}
	}

	int d = 1;
	std::vector<std::vector<int>> temp;

	maze.at(size - 2).at(size - 1) = 1;
	set_point(size - 2, size - 1, RGB(255, 255, 0));

	while (maze.at(1).at(1) == 0) // Donne à chaque case la distance entre sa position et la sortie (ainsi qu'une couleur correspondante)
	{
		temp = maze;
		d++;

		for (int i = size - 2; i > 0; i--)
		{
			for (int j = size - 2; j > 0; j--)
			{
				if (maze.at(i).at(j) == 0)
				{
					if (maze.at(i - 1).at(j) > 0 or maze.at(i + 1).at(j) > 0 or maze.at(i).at(j - 1) > 0 or maze.at(i).at(j + 1) > 0)
					{
						temp.at(i).at(j) = d;
						set_point(i, j, color(d, size * 1.5));
					}
				}
			}
		}

		maze = temp;
	}

	maze.at(1).at(0) = d + 20;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (maze.at(i).at(j) == 0)
				maze.at(i).at(j) = d + 1;

			if (maze.at(i).at(j) == -1)
				maze.at(i).at(j) = d + 10;
		}
	}

	set_point(1, 0, RGB(0, 255, 0));
	set_point(1, 1, RGB(0, 255, 0));

	int x = 1;
	int y = 1;

	while (x != size - 2 or y != size - 2) // Trace le chemin vert (le chemin le plus court entre l'entrée et la sortie)
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

	set_point(size - 2, size - 1, RGB(0, 255, 0));
}



// ---------- Le main ----------



int main()
{
	int nb_simulation = 100; // Choisir le nombre de simulations
	set_size(100); // Choisir la taille du labyrinthe

	for (int s = 0; s < nb_simulation; s++)
	{
		create_grid();
		show();
		maze_generator(1);

		maze_solver();

		Sleep(1000);

		maze.clear();
		system("cls");
	}

	return 0;
}