#pragma once

#include <queue>
#include "Screen.hpp"
#include "GameObject.hpp"
#include "CollisionModel.hpp"
#include "Player.hpp"
#include "Bonus.hpp"
#include "Obstacle.hpp"
#include "DeathParticle.hpp"
#include "Cloud.hpp"
#include "MiniMap.hpp"
#include "Ground.hpp"

enum GameState
{
	PAUSED, // The player hit pause
	PLAYING, // Regular gameplay
	LANDING, // The player is at the last part (freeze camera movement)
	GAMEOVER, // The player died a horrible death
	SAVED, // The player landed safely on the ground. Time to save
	NEXTLEVEL // The player went through to the next level. Badass.
};

class GameScreen : public Screen
{
public:
	GameScreen(void);
	~GameScreen(void);

	std::vector<GameObject*> mGameObjects;
	std::vector<GameObject*> mRenderables;
	// Death animation things
	std::vector<GameObject*> mDeathObjects;

	// Used for collision checking
	std::queue<CollisionInfo*> mCollidedObjects;

	Player * player;
	// The speed the player is currently falling
	float mFallSpeed;

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;
	void sendKey(sf::Keyboard::Key key) override;

	// The gravity. Used to accelerate FallSpeed
	const float GRAVITY;
	// The maxiumum speed a player can fall
	const float MAX_FALL_VELOCITY;
	const float MIN_FALL_VELOCITY;

	sf::Font mFont_ubuntu;
	sf::Text DEBUGTEXT;

	// A list of debugging for labels!
	std::pair<std::string, float> * DEBUGLABELS;
	// some debug consts to display and modify the debug data
	const int DBG_FALLSPEED;
	const int DBG_TRAVELED;
	const int DBG_PLAYER_YVEL;

	// How much one of the score powerups is worth
	const int SCORE_VALUE;

	// Displays the score on the right side
	sf::Text mScoreText;

private:
	// The following mLevelx things are used to determine the level's end zone
	// The distance the player must travel
	float mLevelDistance;
	// How many units the player has traveled so far
	float mLevelTraveled;

	GameState mState;
	int mPlayerScore;
	// Handles the game PLAYING state logic
	void gameTick(float delta);
	// Handles the game playing the DEATH logic
	void deathTick(float delta);
	// Handles the game where the player is landing (aka: has reached the end)
	void landingTick(float delta);
	// Handles the game when the player has safely landed and is safe (but done)
	void savedTick(float delta);

	void runCollisionChecks();

	// This is going to be a big mess. Restarts the level
	void resetLevel();

	// This is the game's background. It will gradually change based on
	// how close you are to the end
	sf::VertexArray bgverts;
	
	// The four colors. Starting and ending for the top and bottom.
	// These colors get lerped from start to end as you get closer to the
	// end of the level
	sf::Color bgUpStartColor;
	sf::Color bgUpEndColor;
	sf::Color bgDownStartColor;
	sf::Color bgDownEndColor;

	// Adds a RENDERABLE which is ignored by 
	// the collision system completely
	GameObject* addRenderable(GameObject* renderMe);
	GameObject* removeRenderable(GameObject* dontRenderMe);
	// Adds a GameObject, which is both rendered AND considered
	// for collision
	GameObject* addGameObject(GameObject* go);
	GameObject* removeGameObject(GameObject* goBye);

	MiniMap* mMiniMap;
};

