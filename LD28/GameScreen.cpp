#include "GameScreen.hpp"


GameScreen::GameScreen(void) : GRAVITY(50.0f), MAX_FALL_VELOCITY(1000.0f), MIN_FALL_VELOCITY(150.0f),
	mPlayerScore(0), mState(GameState::PLAYING),
	DEBUGFONT(), DEBUGTEXT("DEBUG", DEBUGFONT), mScoreText("Score: 0", DEBUGFONT)
{
	this->mID = "GameScreen";
	mFallSpeed = 0.0f;

	// Make the player
	player = new Player();
	mGameObjects.push_back(player);

	// Add some bonuses
	Bonus* bonus;
	for(int i = 0; i < 150; ++i)
	{
		bonus = new Bonus();
		bonus->name = "Bonus " + std::to_string(i);
		mGameObjects.push_back(bonus);

		bonus->position.x = rand() % 450 + 25;
		bonus->position.y = 500.0f + i * 150.0f;
	}

	// Add some obstacles
	Obstacle* obs = new Obstacle();
	obs->position.x = 250;
	obs->position.y = 600;
	mGameObjects.push_back(obs);

	DEBUGFONT.loadFromFile("assets/fonts/UbuntuMono.ttf");
	DEBUGTEXT.setCharacterSize(10);
	DEBUGTEXT.setStyle(sf::Text::Regular);
	DEBUGTEXT.setColor(sf::Color::Green);
	DEBUGTEXT.setPosition(5.0f, 10.0f);

	mScoreText.setCharacterSize(12);
	mScoreText.setStyle(sf::Text::Regular);
	mScoreText.setColor(sf::Color::White);
	mScoreText.setPosition(400.0f, 10.0f);
}


GameScreen::~GameScreen(void)
{
}

void GameScreen::update(float delta)
{
	switch (mState)
	{
	case PAUSED:
		break;
	case PLAYING:
		gameTick(delta);
		break;
	case GAMEOVER:
		deathTick(delta);
		break;
	default:
		break;
	}
	
}

void GameScreen::gameTick(float delta)
{
	// Update the falling speed
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mFallSpeed -= GRAVITY * delta;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mFallSpeed += GRAVITY * delta * 2;
	}
	else
	{
		mFallSpeed += GRAVITY * delta;
	}
	if(mFallSpeed <= MIN_FALL_VELOCITY)
	{
		mFallSpeed = MIN_FALL_VELOCITY;
	}
	if(mFallSpeed >= MAX_FALL_VELOCITY)
	{
		mFallSpeed = MAX_FALL_VELOCITY;
	}

	DEBUGTEXT.setString("Fall Speed: " + std::to_string(mFallSpeed));

	GameObject* currObj;
	GameObject* otherObj;

	// Do collision detection before moving people. For now this is going to have to 
	// be a naive collision detection
	for(int n = 0; n < mGameObjects.size(); ++n)
	{
		currObj = mGameObjects[n];
		for(int m = 0; m < mGameObjects.size(); ++m)
		{
			otherObj = mGameObjects[m];
			// Skip if this == this
			if(n == m) continue;
			// If current is supposed to collide with other
			if(currObj->checkCollidesWith(otherObj->getCollisionType()))
			{
				if(currObj->mCollision->isColliding(*otherObj->mCollision))
				{
					// Create the CollisionInfo to push to the stack
					mCollidedObjects.push(new CollisionInfo(currObj, otherObj));
				}
			}
		}
	}

	// Now that we have all the collided things, let's go through them and nuke
	CollisionInfo* currPod;
	while(mCollidedObjects.size() > 0)
	{
		currPod = mCollidedObjects.front();
		// Process
		switch (currPod->source->getCollisionType())
		{
		case CollisionFlags::OBSTACLE:
			std::cout << "Obstacle hit! Kill the player" << std::endl;
			// Change the game state to gameover man, game over!
			mState = GameState::GAMEOVER;
			break;
		case CollisionFlags::PLAYER:
			if(currPod->target->checkCollisionType(CollisionFlags::SCORE))
			{
				std::cout << "Player scored" << std::endl;
				++mPlayerScore;
				// Update the score text
				mScoreText.setString("Score: " + std::to_string(mPlayerScore));
				// Use the Erase-remove idiom to remove the bonus
				std::remove(std::begin(mGameObjects), std::end(mGameObjects),currPod->target);
				// and destroy it
				delete(currPod->target);
			}
			break;
		case CollisionFlags::SCORE:
			break;
		default:
			break;
		}
		mCollidedObjects.pop();
	}
	
	// Now update each gameobject. Delete it if it no longer should exist
	for(std::vector<GameObject*>::iterator itor = mGameObjects.begin(); itor != mGameObjects.end();)
	{
		currObj = (*itor);
		// If the given gameobject isn't the player, push it with gravity
		if(!currObj->checkCollisionType(CollisionFlags::PLAYER))
		{
			currObj->position.y -= mFallSpeed * delta;
		}
		currObj->update(delta);
		// Iterate if all is well
		++itor;
	}
}

void GameScreen::deathTick(float delta)
{
	// If death hasn't been initialized (ie: the death animation hasn't started) start it
	if(mDeathObjects.size() == 0)
	{
		// This is a list of directions.  Basically it's an array of Vectors without the overhead
		int numDirs = 8;
		// Start pointing straight right, then spiral around clockwise
		int xDir[] = { 1, 1, 0,-1,-1,-1, 0, 1};
		int yDir[] = { 0, 1, 1, 1, 0,-1,-1,-1};
		float velocity = 50.0f;
		DeathParticle* tPart;
		// Build a bunch of death particles
		for(int i = 0; i < 16; ++i)
		{
			tPart = new DeathParticle(xDir[i % numDirs], yDir[i % numDirs], velocity * ((i > numDirs*0.5)?2:1));
			tPart->position.x = player->position.x;
			tPart->position.y = player->position.y;
			mDeathObjects.push_back(tPart);
			// Push it to GameObjects to automagically handle drawing. This should probably be extracted
			// into a renderables list, and a gameobjects list, but for jam, not necessary
			mGameObjects.push_back(tPart);
		}

		// Now hide the player so it doesn't render anymore
		// Another reason to use the renderables list and not the gameobjects list :/
		std::remove(std::begin(mGameObjects), std::end(mGameObjects),player);

	}

	// Meow update them all
	for(std::vector<GameObject*>::iterator itor = mDeathObjects.begin(); 
		itor != mDeathObjects.end();
		++itor)
	{
		(*itor)->update(delta);
	}

}

void GameScreen::sendKey(sf::Keyboard::Key key)
{
	switch(key)
	{
	case sf::Keyboard::P:
		// Toggle pausing IFF the state is playing or paused
		if(mState == GameState::PAUSED || mState == GameState::PLAYING)
		{
			mState = (mState == GameState::PAUSED)?GameState::PLAYING:GameState::PAUSED;
		}
		break;
	default:
		break;
	}
}

void GameScreen::draw(sf::RenderWindow& window)
{
	// Do draw shit here
	for(int i = 0; i < mGameObjects.size(); ++i)
	{
		mGameObjects[i]->draw(window);
	}
	window.draw(DEBUGTEXT);
	window.draw(mScoreText);
}