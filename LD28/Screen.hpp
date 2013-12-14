#pragma once

#include <SFML\Graphics.hpp>

class Screen
{
public:
	Screen(void);
	~Screen(void);

	void update(sf::Time delta);
	void draw(sf::RenderWindow& window);
};

