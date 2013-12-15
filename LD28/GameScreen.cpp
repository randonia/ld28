#include "GameScreen.hpp"


GameScreen::GameScreen(void) : GRAVITY(50.0f), MAX_FALL_VELOCITY(1000.0f), MIN_FALL_VELOCITY(150.0f),
	mPlayerScore(0), mState(GameState::PLAYING), bgverts(sf::Quads,4),
	bgUpStartColor(76,201,255), bgUpEndColor(54,141,178), bgDownStartColor(61,161,204), bgDownEndColor(42,111,140),
	mFont_ubuntu(), DEBUGTEXT("DEBUG", mFont_ubuntu), mScoreText("Score: 0", mFont_ubuntu),
	DBG_FALLSPEED(0),DBG_TRAVELED(1)
{
	this->mID = "GameScreen";
	mFallSpeed = 0.0f;

	// Make the player
	player = new Player();
	addGameObject(player);

	// Initialize some basic level data
	mLevelTraveled = 0.0f;
	mLevelDistance = 10000.0f;

	// Build the background verts (for the changing background)
	bgverts[0] = sf::Vertex(sf::Vector2<float>(0.0f,0.0f), bgUpStartColor);
	bgverts[1] = sf::Vertex(sf::Vector2<float>(500.0f,0.0f), bgUpStartColor);
	bgverts[2] = sf::Vertex(sf::Vector2<float>(500.0f,700.0f), bgDownStartColor);
	bgverts[3] = sf::Vertex(sf::Vector2<float>(0.0f,700.0f), bgDownStartColor);

	float maxObjectDistance = -1.0;

	// Add some bonuses
	Bonus* bonus;
	for(int i = 0; i < 150; ++i)
	{
		bonus = new Bonus();
		bonus->name = "Bonus " + std::to_string(i);
		bonus->position.x = rand() % 325 + 25;
		bonus->position.y = 500.0f + i * 150.0f;
		// Make sure we don't go too far yo
		if(bonus->position.y > mLevelDistance) break;

		addGameObject(bonus);

		if(bonus->position.y > maxObjectDistance) maxObjectDistance = bonus->position.y;
	}

	// Add some obstacles
	Obstacle* obs;
	for(int o = 0; o < 25; ++o)
	{
		obs = new Obstacle();
		obs->position.x = rand() % 325 + 25;
		obs->position.y = (rand() % 100 + 250 * (o + 2));
		if(obs->position.y > mLevelDistance) break;
		addGameObject(obs);
		if(obs->position.y > maxObjectDistance) maxObjectDistance = obs->position.y;
	}

	// Add some clouds
	Cloud* tCloud;	
	for(int c = 0; c < 200; ++c)
	{
		tCloud = new Cloud();
		tCloud->position.x = rand() % 400;
		tCloud->position.y = (rand() % 100 * c);
		if(tCloud->position.y > mLevelDistance) break;
		addRenderable(tCloud);
		if(tCloud->position.y > maxObjectDistance) maxObjectDistance = tCloud->position.y;
	}

	// Add the ground
	Ground* tGround;
	tGround = new Ground();
	tGround->position.x = 200;
	tGround->position.y = 500;
	addGameObject(tGround);


	// Build the minimap
	mMiniMap = new MiniMap();
	mMiniMap->mDistance = maxObjectDistance;
	// TODO: Figure out what's up with the MiniMap
	//mMiniMap->preDrawObjects(mRenderables);
	
	// ******** Font dealings *********

	// Load the text font for text drawing
	mFont_ubuntu.loadFromFile("assets/fonts/UbuntuMono.ttf");

	// Display the score
	mScoreText.setCharacterSize(12);
	mScoreText.setStyle(sf::Text::Regular);
	mScoreText.setColor(sf::Color::Blue);
	mScoreText.setPosition(400.0f, 10.0f);


	DEBUGTEXT.setCharacterSize(10);
	DEBUGTEXT.setStyle(sf::Text::Regular);
	DEBUGTEXT.setColor(sf::Color::Black);
	DEBUGTEXT.setPosition(5.0f, 10.0f);

	DEBUGLABELS = new std::pair<std::string, float>[2];
	DEBUGLABELS[DBG_FALLSPEED] = std::make_pair("Fallspeed: ", 0.0f);
	DEBUGLABELS[DBG_TRAVELED] = std::make_pair("Distance Traveled: ", 0.0f);
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
	
	// Update the debug data
	DEBUGLABELS[DBG_FALLSPEED].second = mFallSpeed;
	DEBUGLABELS[DBG_TRAVELED].second = mLevelTraveled;

	std::string dbgResult = "";
	for(int i = 0; i < 2; ++i)
	{
		dbgResult += DEBUGLABELS[i].first + std::to_string(DEBUGLABELS[i].second) + "\n";
	}
	DEBUGTEXT.setString(dbgResult);
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

	DEBUGTEXT.setString("Fall Speed: " + std::to_string(mFallSpeed) + "\nFoo");

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
			// If the player collided with a score object, give them points
			if(currPod->target->checkCollisionType(CollisionFlags::SCORE))
			{
				std::cout << "Player scored" << std::endl;
				++mPlayerScore;
				// Update the score text
				mScoreText.setString("Score: " + std::to_string(mPlayerScore));
				// Use the Erase-remove idiom to remove the bonus
				removeGameObject(currPod->target);
				// and destroy it
				delete(currPod->target);
			}
			// If they collided with the ground, we must do checks to see if they're going to survive or not
			// Must check their parachute status
			else if (currPod->target->checkCollisionType(CollisionFlags::GROUND))
			{

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
	for(std::vector<GameObject*>::iterator itor = mRenderables.begin(); itor != mRenderables.end();)
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

	// Move the marker forward!
	mLevelTraveled += mFallSpeed * delta;
	mMiniMap->updateMarker(mLevelTraveled / mLevelDistance);
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
		for(int i = 0; i < 33; ++i)
		{
			tPart = new DeathParticle(xDir[i % numDirs], yDir[i % numDirs], velocity * (i + 1)/ numDirs);
			tPart->position.x = player->position.x;
			tPart->position.y = player->position.y;
			mDeathObjects.push_back(tPart);
			// Push it to GameObjects to automagically handle drawing. This should probably be extracted
			// into a renderables list, and a gameobjects list, but for jam, not necessary
			addRenderable(tPart);
		}

		// Now hide the player so it doesn't render anymore
		// Another reason to use the renderables list and not the gameobjects list :/
		removeGameObject(player);

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

void GameScreen::draw(sf::RenderTarget& window)
{
	// Do draw shit here
	window.draw(bgverts);
	for(std::vector<GameObject*>::iterator drawtor = mRenderables.begin();
		drawtor != mRenderables.end();
		++drawtor)
	{
		(*drawtor)->draw(window);
	}
	mMiniMap->draw(window);
	window.draw(DEBUGTEXT);
	window.draw(mScoreText);
}

GameObject* GameScreen::addRenderable(GameObject* renderMe)
{
	mRenderables.push_back(renderMe);
	return renderMe;
}

GameObject*  GameScreen::removeRenderable(GameObject* dontRenderMe)
{
	mRenderables.erase(std::remove(std::begin(mRenderables), std::end(mRenderables), dontRenderMe));
	return dontRenderMe;
}

GameObject*  GameScreen::addGameObject(GameObject* go)
{
	// Use the built in code
	addRenderable(go);
	mGameObjects.push_back(go);
	return go;
}

GameObject*  GameScreen::removeGameObject(GameObject* goBye)
{
	removeRenderable(goBye);
	mGameObjects.erase(std::remove(std::begin(mGameObjects), std::end(mGameObjects), goBye));
	return goBye;
}