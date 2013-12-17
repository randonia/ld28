#include <string>
#include <iostream>
#include <stack>

#include <SFML/Graphics.hpp>

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

	// Set up the window to just have a title bar. Might fix the X button audio bug
	sf::RenderWindow window(sf::VideoMode(500,700), "Don't Deploy Your Chute - LD48",sf::Style::Titlebar);

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
	FPSText.setOrigin(0.0f,2.0f);
	
	bool drawFPS = false;
	bool mFKeyReleased = true;

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
			FPSText.setString("FPS: " + std::to_string((FPS)));
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			if(mFKeyReleased)
			{
				drawFPS = !drawFPS;
				mFKeyReleased = false;
			}
		}
		else
		{
			mFKeyReleased = true;
		}

		window.clear(sf::Color::Black);
		// Update the first screen
		screens.top()->update(deltaTime);
		screens.top()->draw(window);
		if(drawFPS)
		{
			FPSText.setPosition(1.0f,1.0f);
			FPSText.setColor(sf::Color::Black);
			window.draw(FPSText);
			FPSText.setColor(sf::Color::Yellow);
			FPSText.setPosition(0.0f,0.0f);
			window.draw(FPSText);
		}
		window.display();
	}

	return 0;
}