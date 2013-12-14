#include "GameScreen.hpp"


GameScreen::GameScreen(void) : GRAVITY(9.8f), MAX_FALL_VELOCITY(20.0f)
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
	// Update the falling speed
	mFallSpeed += GRAVITY * delta;
	if(mFallSpeed >= MAX_FALL_VELOCITY)
	{
		mFallSpeed = MAX_FALL_VELOCITY;
	}

	GameObject* currObj;
	for(int i = 0; i < mGameObjects.size(); ++i)
	{
		currObj = mGameObjects[i];
		// If the given gameobject isn't the player, push it with gravity
		if(!currObj->checkCollisionFlags(CollisionFlags::PLAYER))
		{
			currObj->position.y -= mFallSpeed * delta;
		}
		currObj->update(delta);
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