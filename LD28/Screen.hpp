#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

class Screen
{
public:
	Screen(void);
	virtual ~Screen(void);
	// The 'Tick' phase
	virtual void update(sf::Time& delta);
	// The 'draw' phase. Draws everything to the window
	virtual void draw(sf::RenderWindow& window);
protected:
	// An identification string for debugging purposes
	std::string ID;
};

