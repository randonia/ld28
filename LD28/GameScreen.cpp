#include "GameScreen.hpp"


GameScreen::GameScreen(void)
{
	this->mID = "GameScreen";

	// Add a debug game object
	GameObject* newObject = new GameObject();
	mGameObjects.push_back(newObject);
}


GameScreen::~GameScreen(void)
{
}

void GameScreen::update(sf::Time& delta)
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