#include "GameScreen.hpp"


GameScreen::GameScreen(void)
{
	this->mID = "GameScreen";

	// Make the player
	player = new Player();
	mGameObjects.push_back(player);
}


GameScreen::~GameScreen(void)
{
}

void GameScreen::update(float delta)
{
	for(int i = 0; i < mGameObjects.size(); ++i)
	{
		mGameObjects[i]->update(delta);
	}
}

void GameScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	// Do draw shit here
	for(int i = 0; i < mGameObjects.size(); ++i)
	{
		mGameObjects[i]->draw(window);
	}

	window.display();
}