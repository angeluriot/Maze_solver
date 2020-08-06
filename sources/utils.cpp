#include "utils.h"

void events(sf::Event& sf_event, sf::RenderWindow& window, bool& end)
{
	while (window.pollEvent(sf_event))
	{
		switch (sf_event.type)
		{

		case sf::Event::Closed:

			window.close();
			end = true;
			break;
		}
	}
}