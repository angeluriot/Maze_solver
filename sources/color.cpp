#include "color.h"



// Crée une couleur

Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
}



// Crée une couleur à partir d'une autre

Color::Color(const Color& color)
{
	red = color.red;
	green = color.green;
	blue = color.blue;
}



// Crée une couleur à partir de ses composantes rouges, vertes et bleues

Color::Color(int red, int green, int blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}



// Assignation

void Color::operator=(const Color& color)
{
	red = color.red;
	green = color.green;
	blue = color.blue;
}



// Donne une couleur à partir de la distance entre une case et la sortie

Color color(int value, const int& max_value)
{
	value = int(double((double(value) / double(max_value)) * double(255)));

	if (value <= 255)
		return Color(255, 255 - value, 0);

	if (value > 255 and value <= 255 * 2)
		return Color(2 * 255 - value, 0, value - 255);

	if (value > 255 * 2 and value <= 255 * 3)
		return Color(0, 0, 255 * 3 - value);

	return Color(0, 0, 0);
}