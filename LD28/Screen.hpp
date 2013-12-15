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
	virtual void update(float delta);
	// The 'draw' phase. Draws everything to the window
	virtual void draw(sf::RenderTarget& window);
	// Use this to send keys to the screens. That way multi-polling doesn't have to occur
	virtual void sendKey(sf::Keyboard::Key key){}

	void (*fAddScreen)(Screen*);
	void (*fRemoveScreen)();
	
protected:
	// An identification string for debugging purposes
	std::string mID;
};

