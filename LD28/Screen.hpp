#pragma once

#include <SFML\Graphics.hpp>

class Screen
{
public:
	Screen(void);
	~Screen(void);

	virtual void update(sf::Time& delta);
	virtual void draw(sf::RenderWindow& window);
};

