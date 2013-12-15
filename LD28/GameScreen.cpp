#include "GameScreen.hpp"


GameScreen::GameScreen(void) : GRAVITY(50.0f), MAX_FALL_VELOCITY(500), MIN_FALL_VELOCITY(150.0f),
	GEN_BONUS_COUNT(250), GEN_OBSTACLE_COUNT(400), GEN_CLOUD_COUNT(600),
	mPlayerScore(0), SCORE_VALUE(500), mState(GameState::PLAYING), bgverts(sf::Quads,4), SAVED_STATE_DELAY(1500.0f),
	bgUpStartColor(76,201,255), bgUpEndColor(54,141,178), bgDownStartColor(61,161,204), bgDownEndColor(42,111,140),
	mFont_ubuntu(), DEBUGTEXT("DEBUG", mFont_ubuntu), 
	mPromptText("Prompt", mFont_ubuntu), mScoreText("Score: 0", mFont_ubuntu),
	DBG_FALLSPEED(0),DBG_TRAVELED(1), DBG_PLAYER_YVEL(2)
{
	this->mID = "GameScreen";
	mFallSpeed = 0.0f;

	// try loading the bgm
	if(!mBGM.openFromFile("assets/audio/bgtrack.ogg"))
	{
		std::cerr << "Unable to load background audio track" << std::endl;
	}
	mBGM.setVolume(mBGM.getVolume() * 0.9f);
	mBGM.play();
	mBGM.setLoop(true);

	if(!mSmashBuff.loadFromFile("assets/audio/hit_hurt.wav"))
	{
		std::cerr << "Unable to load hit_hurt audio track" << std::endl;
	}
	mSmash.setBuffer(mSmashBuff);
	
	if(!mScoreBuff.loadFromFile("assets/audio/score.wav"))
	{
		std::cerr << "Unable to load score audio track" << std::endl;
	}
	mScore.setBuffer(mScoreBuff);

	if(!mYeahBuff.loadFromFile("assets/audio/yea.ogg"))
	{
		std::cerr << "Unable to load yea audio track" << std::endl;
	}
	mYeah.setBuffer(mYeahBuff);
	


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
	for(int i = 0; i < GEN_BONUS_COUNT; ++i)
	{
		bonus = new Bonus();
		bonus->name = "Bonus " + std::to_string(i);
		bonus->position.x = rand() % 425 + 25;
		bonus->position.y = 500.0f + i * 150.0f;
		// Make sure we don't go too far yo
		if(bonus->position.y > mLevelDistance) break;

		addGameObject(bonus);

		if(bonus->position.y > maxObjectDistance) maxObjectDistance = bonus->position.y;
	}

	// Add some obstacles
	Obstacle* obs;
	for(int o = 0; o < GEN_OBSTACLE_COUNT; ++o)
	{
		obs = new Obstacle();
		obs->position.x = rand() % 425 + 25;
		obs->position.y = (rand() % 100 + 250 * (o + 2));
		if(obs->position.y > mLevelDistance) break;
		addGameObject(obs);
		if(obs->position.y > maxObjectDistance) maxObjectDistance = obs->position.y;
	}

	// Add some clouds
	Cloud* tCloud;	
	for(int c = 0; c < GEN_CLOUD_COUNT; ++c)
	{
		tCloud = new Cloud();
		tCloud->position.x = rand() % 400;
		tCloud->position.y = (rand() % 100 * c);
		if(tCloud->position.y > mLevelDistance) break;
		addRenderable(tCloud);
		if(tCloud->position.y > maxObjectDistance) maxObjectDistance = tCloud->position.y;
	}

	// Add the ground. Basically make it a straight line, except in the middle.
	// 5 on the left, 5 on the right
	Ground* tGround;
	const int groundY = mLevelDistance + 550.0f;
	//const int groundY = 350;

	for(int g = 0; g < 5; ++g)
	{
		// Make the left side
		tGround = new Ground();
		tGround->position.x = 16 + g * 32;
		//tGround->position.y = mLevelDistance + 250.0f;
		tGround->position.y = groundY;
		addGameObject(tGround);

		// Meow make the right side
		tGround = new Ground();
		tGround->position.x = 450 - (16 + g * 32);
		tGround->position.y = groundY;
		addGameObject(tGround);
	}


	// Build the minimap
	mMiniMap = new MiniMap();
	mMiniMap->mDistance = maxObjectDistance;
	// TODO: Figure out what's up with the MiniMap
	//mMiniMap->preDrawObjects(mRenderables);
	
	// ******** Font dealings *********

	// Load the text font for text drawing
	mFont_ubuntu.loadFromFile("assets/fonts/UbuntuMono.ttf");

	// Display the score
	mScoreText.setCharacterSize(18);
	mScoreText.setStyle(sf::Text::Regular);
	mScoreText.setColor(sf::Color::Blue);
	mScoreText.setPosition(320.0f, 10.0f);

	mPromptText.setCharacterSize(20);
	mPromptText.setStyle(sf::Text::Regular);
	mPromptText.setPosition(250.0f, 450.0f);
	mPromptText.setColor(sf::Color::White);
	mPromptText.setString("Press [R] to restart the level");
	mPromptText.setOrigin(mPromptText.getLocalBounds().width * 0.5f, mPromptText.getLocalBounds().height * 0.5f);


	DEBUGTEXT.setCharacterSize(10);
	DEBUGTEXT.setStyle(sf::Text::Regular);
	DEBUGTEXT.setColor(sf::Color::Black);
	DEBUGTEXT.setPosition(5.0f, 10.0f);

	DEBUGLABELS = new std::pair<std::string, float>[3];
	DEBUGLABELS[DBG_FALLSPEED] = std::make_pair("Fallspeed: ", 0.0f);
	DEBUGLABELS[DBG_TRAVELED] = std::make_pair("Distance Traveled: ", 0.0f);
	DEBUGLABELS[DBG_PLAYER_YVEL] = std::make_pair("Player Y Velocity: ", 0.0f);
}

void GameScreen::resetLevel()
{
	// First re-initialize all the shit in the gamescreen constructor
	mState = GameState::PLAYING;
	//mFallSpeed = 0.0f;

	// Pwn out all the gameobjects
	while(mGameObjects.size() > 0)
	{
		removeGameObject(mGameObjects.front());
	}
	// Then clear our ALL the renderables and gameobjects
	while(mRenderables.size() > 0)
	{
		removeRenderable(mRenderables.front());
	}
	while(mDeathObjects.size() > 0)
	{
		mDeathObjects.pop_back();
	}

	// Then reset the player
	player->reset();
	// Don't forget to friggin add the player back
	addGameObject(player);

	mLevelTraveled = 0.0f;
	bgverts[0].color = bgUpStartColor;
	bgverts[1].color = bgUpStartColor;
	bgverts[2].color = bgDownStartColor;
	bgverts[3].color = bgDownStartColor;

	float maxObjectDistance = -1.0;

	// Add some bonuses
	Bonus* bonus;
	for(int i = 0; i < GEN_BONUS_COUNT; ++i)
	{
		bonus = new Bonus();
		bonus->name = "Bonus " + std::to_string(i);
		bonus->position.x = rand() % 425 + 25;
		bonus->position.y = 500.0f + i * 150.0f;
		// Make sure we don't go too far yo
		if(bonus->position.y > mLevelDistance) break;

		addGameObject(bonus);

		if(bonus->position.y > maxObjectDistance) maxObjectDistance = bonus->position.y;
	}

	// Add some obstacles
	Obstacle* obs;
	for(int o = 0; o < GEN_OBSTACLE_COUNT; ++o)
	{
		obs = new Obstacle();
		obs->position.x = rand() % 425 + 25;
		obs->position.y = (rand() % 250 + 100 * (o + 2));
		if(obs->position.y > mLevelDistance) break;
		addGameObject(obs);
		if(obs->position.y > maxObjectDistance) maxObjectDistance = obs->position.y;
	}

	// Add some clouds
	Cloud* tCloud;	
	for(int c = 0; c < GEN_CLOUD_COUNT; ++c)
	{
		tCloud = new Cloud();
		tCloud->position.x = rand() % 400 + 25;
		tCloud->position.y = (rand() % 100 * c);
		if(tCloud->position.y > mLevelDistance) break;
		addRenderable(tCloud);
		if(tCloud->position.y > maxObjectDistance) maxObjectDistance = tCloud->position.y;
	}

	// Add the ground. Basically make it a straight line, except in the middle.
	// 5 on the left, 5 on the right
	Ground* tGround;
	const int groundY = mLevelDistance + 550.0f;
	//const int groundY = 350;

	for(int g = 0; g < 5; ++g)
	{
		// Make the left side
		tGround = new Ground();
		tGround->position.x = 16 + g * 32;
		//tGround->position.y = mLevelDistance + 250.0f;
		tGround->position.y = groundY;
		addGameObject(tGround);

		// Meow make the right side
		tGround = new Ground();
		tGround->position.x = 450 - (16 + g * 32);
		tGround->position.y = groundY;
		addGameObject(tGround);
	}
	
	mMiniMap->reset();
	mMiniMap->mDistance = maxObjectDistance;

	// Resume the shitty bgm
	mSmash.stop();
	if(mBGM.getStatus() != sf::Music::Playing)
	{
		mBGM.play();
	}
}

GameScreen::~GameScreen(void)
{
	
}

void GameScreen::update(float delta)
{
	// Check for pausing because polling events blow
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if(mPauseReleased)
		{
			if(mState == GameState::PAUSED || mState == GameState::PLAYING)
			{
				mState = (mState == GameState::PAUSED)?GameState::PLAYING:GameState::PAUSED;
			}
		}
		mPauseReleased = false;
	}
	else
	{
		mPauseReleased = true;
	}

	switch (mState)
	{
	case PAUSED:
		break;
	case PLAYING:
		gameTick(delta);
		break;
	case LANDING:
		landingTick(delta);
		break;
	case GAMEOVER:
		deathTick(delta);
		break;
	case SAVED:
		savedTick(delta);
		break;
	case NEXTLEVEL:
		nextLevelTick(delta);
		break;
	default:
		break;
	}
	
	// Update the debug data
	DEBUGLABELS[DBG_FALLSPEED].second = mFallSpeed;
	DEBUGLABELS[DBG_TRAVELED].second = mLevelTraveled;
	DEBUGLABELS[DBG_PLAYER_YVEL].second = player->velocity.y;

	std::string dbgResult = "";
	for(int i = 0; i < 3; ++i)
	{
		dbgResult += DEBUGLABELS[i].first + std::to_string(DEBUGLABELS[i].second) + "\n";
	}
	DEBUGTEXT.setString(dbgResult);
}

void GameScreen::gameTick(float delta)
{
	// This is bad, but I don't care. I'm letting the player's state
	// dictate what happens here
	
	switch (player->mChuteState)
	{
	case ParachuteState::CLOSED:
	case ParachuteState::DEPLOYING:
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
		break;
	case ParachuteState::OPEN:
		mFallSpeed -= GRAVITY;
		break;
	case ParachuteState::BONED:
		// Get fucked
		mFallSpeed += GRAVITY;
	default:
		break;
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

	// Do Collision processing
	runCollisionChecks();
	
	GameObject* currObj;

	// If we're at the end of the level, change game states
	if(mLevelTraveled > mLevelDistance)
	{
		mState = GameState::LANDING;
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

	// Do a player bounce check
	// Do a bounce check
	if(player->position.x <= Player::BOUNDS_LEFT)
	{
		// Bounce
		player->velocity.x *= -1;
		// and move them a bit
		player->position.x = Player::BOUNDS_LEFT;
	}
	if(player->position.x >= Player::BOUNDS_RIGHT)
	{
		player->velocity.x *= -1;
		player->position.x = Player::BOUNDS_RIGHT;
	}
	if(player->position.y <= Player::BOUNDS_UP)
	{
		player->position.y = Player::BOUNDS_UP;
	}
	if(player->position.y >= Player::BOUNDS_DOWN)
	{
		player->position.y = Player::BOUNDS_DOWN;
	}

	// Move the marker forward!
	mLevelTraveled += mFallSpeed * delta;
	mPlayerScore += (2 * mFallSpeed - MIN_FALL_VELOCITY) * delta;
	
	// Update the score text
	mScoreText.setString("Score: " + std::to_string(mPlayerScore));
	mMiniMap->updateMarker(mLevelTraveled / mLevelDistance);
}

void GameScreen::deathTick(float delta)
{

	// If the player hits "R", restart the game
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		resetLevel();
		mPlayerScore = 0;
	}
	else
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

			// Change the player to not render
			player->mRenderingEnabled = false;
		}

		// Meow update them all
		for(std::vector<GameObject*>::iterator itor = mDeathObjects.begin(); 
			itor != mDeathObjects.end();
			++itor)
		{
			(*itor)->update(delta);
		}
	}
}

void GameScreen::landingTick(float delta)
{
	// If the player's chute is open, slow their ass down
	switch (player->mChuteState)
	{
	case ParachuteState::CLOSED:
	case ParachuteState::DEPLOYING:
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
		break;
	case ParachuteState::OPEN:
		mFallSpeed -= GRAVITY;
		break;
	case ParachuteState::BONED:
		// Get fucked
		mFallSpeed += GRAVITY;
	default:
		break;
	}

	if(mFallSpeed <= MIN_FALL_VELOCITY)
	{
		mFallSpeed = MIN_FALL_VELOCITY;
	}
	if(mFallSpeed >= MAX_FALL_VELOCITY)
	{
		mFallSpeed = MAX_FALL_VELOCITY;
	}

	player->position.y += mFallSpeed * delta;
	player->update(delta);
	runCollisionChecks();

	// See if the player has gone past the end of the map. If they have (and not died) then 
	// congratulate them and restart the level preserving the score!
	if(player->position.y > 725.0f)
	{
		mState = GameState::NEXTLEVEL;
	}
}

void GameScreen::savedTick(float delta)
{
	// If the delay has expired, add the score graphic on screen
	if(mSaveTimer.getElapsedTime().asMilliseconds() > SAVED_STATE_DELAY)
	{
		HighScoreScreen* highscore = new HighScoreScreen(mPlayerScore);
		highscore->fAddScreen = fAddScreen;
		highscore->fRemoveScreen = fRemoveScreen;
		fRemoveScreen();
		mBGM.stop();
		fAddScreen(highscore);
	}
}

void GameScreen::nextLevelTick(float delta)
{
	// Maybe do some fancy animation. But for now, just give them a fat score bonus 
	// and reset the level
	// We have to see if the player messed up and deployed his/her chute though
	if(player->mChuteState == ParachuteState::CLOSED)
	{
		mPlayerScore += 10000.0f;
		resetLevel();
	}
	else
	{
		resetLevel();
		player->setBoned();
	}
}

void GameScreen::runCollisionChecks()
{
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
			player->velocity.x = 0.0f;
			player->velocity.y = 0.0f;
			mFallSpeed = 0.0f;
			// Change the game state to gameover man, game over!
			mState = GameState::GAMEOVER;
			// Queue the shitty audio
			mBGM.pause();
			mSmash.play();
			break;
		case CollisionFlags::PLAYER:
			// If the player collided with a score object, give them points
			if(currPod->target->checkCollisionType(CollisionFlags::SCORE))
			{
				std::cout << "Player scored" << std::endl;
				mScore.play();
				mPlayerScore += SCORE_VALUE;
				// Use the Erase-remove idiom to remove the bonus
				removeGameObject(currPod->target);
				// and destroy it
				delete(currPod->target);
			}
			// If they collided with the ground, we must do checks to see if they're going to survive or not
			// Must check their parachute status
			else if (currPod->target->checkCollisionType(CollisionFlags::GROUND))
			{
				// What happens here depends on the player's parachute
				switch (player->mChuteState)
				{
				case ParachuteState::CLOSED:
				case ParachuteState::BONED:
				case ParachuteState::DEPLOYING:
					// Kill the player
					mState = GameState::GAMEOVER;
					// Queue the shitty audio
					mBGM.pause();
					mSmash.play();
					break;
				case ParachuteState::OPEN:
					// They are safe! Woo hoo!
					std::cout << "Player has safely landed! Woo" << std::endl;
					mYeah.play();
					mState = GameState::SAVED;
					mSaveTimer.restart();
				default:
					break;
				}
			}
			break;
		case CollisionFlags::SCORE:
			break;
		default:
			break;
		}
		mCollidedObjects.pop();
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
	// Draw the prompt text if we're in the death state
	if(mState == GameState::GAMEOVER)
	{
		mPromptText.setPosition(250.0f, 450.0f);
		mPromptText.setColor(sf::Color::Black);
		window.draw(mPromptText);
		mPromptText.setColor(sf::Color::White);
		mPromptText.setPosition(249.0f, 449.0f);
		window.draw(mPromptText);
	}
	window.draw(DEBUGTEXT);
	// Outline the score text as well
	mScoreText.setPosition(320.0f, 10.0f);
	mScoreText.setColor(sf::Color::Black);
	window.draw(mScoreText);
	mScoreText.setPosition(319.0f, 9.0f);
	mScoreText.setColor(sf::Color::White);
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