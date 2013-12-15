#pragma once
#include "gameobject.hpp"
#include <SFML\Graphics.hpp>
#include <math.h>

/* The parachute can be one of three things. Timers will dictate transitions
 * once the player has decided to open the chute
 */
enum ParachuteState
{
	CLOSED, // The player has not pressed deploy yet
	DEPLOYING, // The player just pressed deploy, but is not safe to land yet
	OPEN, // The player can safely land. The player has X seconds before the chute fails
	BONED // The chute has failed. The player is boned.
};

class Player :
	public GameObject
{
public:
	Player();
	~Player();

	// The player has several textures, one for each state
	sf::Texture mFallTexture;
	// When the chute is deploying but not yet open
	sf::Texture mDeployingTexture;
	// When the chute is open and safe
	sf::Texture mOpenTexture;
	// When the chute has been destroyed and the player is boned
	sf::Texture mBonedTexture;
	// The sprite to house the textures
	sf::Sprite sprite;

	// The timer that handles the chute lifecycle
	sf::Clock mChuteTimer;
	// How many milliseconds it takes for the chute to deploy
	const float CHUTE_DEPLOY_TIME;
	// How many milliseconds the chute lives while its deployed
	const float CHUTE_LIFE_TIME;

	// The current velocity of the player (not in GameObject because they 
	// aren't really moving
	sf::Vector2<float> velocity;

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;


	const float LATERAL_ACCELERATION;
	const float MAX_LATERAL_SPEED;
	const float PARACHUTE_LATERAL_SPEED;

	// The lateral boundaries that the player can't go past
	const int BOUNDS_LEFT;
	const int BOUNDS_RIGHT;
	const int BOUNDS_UP;
	const int BOUNDS_DOWN;

	const float DAMPENING_CONST;

	ParachuteState mChuteState;

private:
	void chuteClosedTick(float delta);
	void chuteDeployingTick(float delta);
	void chuteOpenTick(float delta);
	void chuteBonedTick(float delta);
};

