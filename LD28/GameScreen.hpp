#pragma once

#include <queue>
#include "Screen.hpp"
#include "GameObject.hpp"
#include "CollisionModel.hpp"
#include "Player.hpp"
#include "Bonus.hpp"
#include "Obstacle.hpp"
#include "DeathParticle.hpp"

enum GameState
{
	PAUSED,
	PLAYING,
	GAMEOVER
};

class GameScreen : public Screen
{
public:
	GameScreen(void);
	~GameScreen(void);

	std::vector<GameObject*> mGameObjects;
	// Used for collision checking
	std::queue<CollisionInfo*> mCollidedObjects;

	Player * player;
	// The speed the player is currently falling
	float mFallSpeed;

	void update(float delta) override;
	void draw(sf::RenderWindow& window) override;
	void sendKey(sf::Keyboard::Key key) override;

	// The gravity. Used to accelerate FallSpeed
	const float GRAVITY;
	// The maxiumum speed a player can fall
	const float MAX_FALL_VELOCITY;
	const float MIN_FALL_VELOCITY;

	sf::Font DEBUGFONT;
	sf::Text DEBUGTEXT;

	// Displays the score on the right side
	sf::Text mScoreText;

	GameState mState;

	int mPlayerScore;
private:
	// Handles the game PLAYING state logic
	void gameTick(float delta);
	// Handles the game playing the DEATH logic
	void deathTick(float delta);

	// Death animation things
	std::vector<GameObject*> mDeathObjects;
};

