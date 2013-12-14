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
	// Do draw shit here
	for(int i = 0; i < mGameObjects.size(); ++i)
	{
		mGameObjects[i]->draw(window);
	}

	window.draw(DEBUGTEXT);
}