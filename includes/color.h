#ifndef COLOR_H
#define COLOR_H

#define WHITE Color(255, 255, 255)	// Couleur blanche
#define BLACK Color(0, 0, 0)		// Couleur noire
#define GREEN Color(0, 255, 0)		// Couleur verte



// Classe définissant une couleur

class Color
{

public :

	int red;	// Composante rouge
	int green;	// Composante verte
	int blue;	// Composante bleue

	Color();
	Color(const Color& color);
	Color(int red, int green, int blue);

	void operator=(const Color& color);
};

Color color(int value, const int& max_value);

#endif