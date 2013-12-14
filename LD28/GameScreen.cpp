#include "GameScreen.hpp"


GameScreen::GameScreen(void)
{
	this->ID = "GameScreen";
}


GameScreen::~GameScreen(void)
{
}

void GameScreen::update(sf::Time& delta)
{
	
}

void GameScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	// Do draw shit here

	window.display();
}