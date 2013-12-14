#pragma once
#include "Screen.hpp"
class GameScreen : public Screen
{
public:
	GameScreen(void);
	~GameScreen(void);

	void update(sf::Time& delta) override;
	void draw(sf::RenderWindow& window) override;
};

