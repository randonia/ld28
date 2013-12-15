#include <string>
#include <iostream>
#include <stack>

#include <SFML\Graphics.hpp>

#include "Screen.hpp"
#include "GameScreen.hpp"
#include "TitleScreen.hpp"


// Build the screen stack
std::stack<Screen*> screens;

void addScreen(Screen* screenToAdd)
{
	screens.push(screenToAdd);
}

void removeScreen()
{
	// Do some better handling of this
	screens.pop();
}

int main (int argc, char* argv[])
{
	// For determining FPS
	float FPS = 0.0f;
	int frames = 0;
	sf::Clock fpsTimer;

	// Set up the window
	sf::RenderWindow window(sf::VideoMode(500,700), "LD28");

	// Deal with game time for anything that needs it
	sf::Clock clock;
	sf::Clock tick;
	
	sf::Time delta;

	sf::Font DEBUGFONT;
	DEBUGFONT.loadFromFile("assets/fonts/UbuntuMono.ttf");
	sf::Text FPSText("FPS",  DEBUGFONT);
	FPSText.setCharacterSize(10);
	FPSText.setStyle(sf::Text::Regular);
	FPSText.setColor(sf::Color::Green);
	
	sf::Event event;

	// Build the first screen here
	// TODO: Make this start in the game screen!
	TitleScreen* title = new TitleScreen();
	title->fAddScreen = addScreen;
	title->fRemoveScreen = removeScreen;
	screens.push(title);
	//GameScreen* game = new GameScreen();
	//game->fAddScreen = addScreen;
	//screens.push(game);

	while(window.isOpen())
	{
		delta = tick.restart();
		float deltaTime = delta.asSeconds();

		++frames;
		// Calculate the FPS if it's been 1 second
		if(fpsTimer.getElapsedTime().asMilliseconds() > 1000.0f)
		{
			int timepassed = fpsTimer.getElapsedTime().asMilliseconds();
			FPS = 1000.0f / (float)((float)timepassed / (float)frames);
			// Set it to the FPS string
			FPSText.setString(std::to_string((FPS)));
			frames = 0;
			fpsTimer.restart();
		}
		
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
		// Split these up because they're different events
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		window.clear(sf::Color::Black);
		// Update the first screen
		screens.top()->update(deltaTime);
		screens.top()->draw(window);
		window.draw(FPSText);
		window.display();
	}

	return 0;
}