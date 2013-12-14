#include <string>
#include <iostream>
#include <stack>

#include <SFML\Graphics.hpp>

#include "Screen.hpp"


int main (int argc, char* argv[])
{
	// Set up the window
	sf::RenderWindow window(sf::VideoMode(500,700), "LD28");

	// Deal with game time for anything that needs it
	sf::Clock clock;
	sf::Clock tick;
	
	sf::Time delta;

	sf::Font DEBUGFONT;
	DEBUGFONT.loadFromFile("assets/fonts/UbuntuMono.ttf");
	sf::Text text("Debug",  DEBUGFONT);
	text.setCharacterSize(16);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Green);

	// Build the screen stack
	std::stack<Screen> screens;

	sf::Event event;

	while(window.isOpen())
	{
		delta = tick.restart();
		
		// Do polling for events (like close window)
		while(window.pollEvent(event))
		{
			// TODO: PROCESS EVENTS
			// For now, just handle closed event
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Update the first screen
		screens.top().update(delta);
		screens.top().draw(window);
	}

	return 0;
}