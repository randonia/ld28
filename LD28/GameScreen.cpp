#include "GameScreen.hpp"


GameScreen::GameScreen(void) : GRAVITY(50.0f), MAX_FALL_VELOCITY(1000.0f), MIN_FALL_VELOCITY(150.0f),
	DEBUGFONT(), DEBUGTEXT("DEBUG", DEBUGFONT)
{
	this->mID = "GameScreen";
	mFallSpeed = 0.0f;

	// Make the player
	player = new Player();
	mGameObjects.push_back(player);

	// Add some bonuses
	Bonus* bonus;
	for(int i = 0; i < 50; ++i)
	{
		bonus = new Bonus();
		mGameObjects.push_back(bonus);

		bonus->position.x = rand() % 450 + 25;
		bonus->position.y = 500.0f + i * 150.0f;
	}

	DEBUGFONT.loadFromFile("assets/fonts/UbuntuMono.ttf");
	DEBUGTEXT.setCharacterSize(10);
	DEBUGTEXT.setStyle(sf::Text::Regular);
	DEBUGTEXT.setColor(sf::Color::Green);
	DEBUGTEXT.setPosition(5.0f, 0.0f);
}


GameScreen::~GameScreen(void)
{
}

void GameScreen::update(float delta)
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
			break;
		case CollisionFlags::PLAYER:
			if(currPod->target->checkCollisionType(CollisionFlags::SCORE))
			{
				std::cout << "Player scored" << std::endl;
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

void GameScreen::draw(sf::RenderWindow& window)
{
	// Do draw shit here
	for(int i = 0; i < mGameObjects.size(); ++i)
	{
		mGameObjects[i]->draw(window);
	}

	window.draw(DEBUGTEXT);
}