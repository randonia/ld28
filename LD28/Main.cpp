#include <string>
#include <iostream>
#include <stack>

#include <SFML\Graphics.hpp>

#include "Screen.hpp"
#include "GameScreen.hpp"


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
	std::stack<Screen*> screens;

	sf::Event event;

	// Build the first screen here
	// TODO: Make this start in the game screen!
	GameScreen* game = new GameScreen();
	screens.push(game);

	while(window.isOpen())
	{
		delta = tick.restart();
		float deltaTime = delta.asSeconds();
		
		// Do polling for events (like close window)
		while(window.pollEvent(event))
		{
			// TODO: PROCESS EVENTS
			// For now, just handle closed event
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			// Split these up because they're different events
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		// Update the first screen
		screens.top()->update(deltaTime);
		screens.top()->draw(window);
	}

	return 0;
}