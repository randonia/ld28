#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

class Screen
{
public:
	Screen(void);
	virtual ~Screen(void);

	virtual void update(sf::Time& delta);
	virtual void draw(sf::RenderWindow& window);
protected:
	std::string ID;
};

