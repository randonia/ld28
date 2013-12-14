#pragma once
#include "gameobject.hpp"
#include <SFML\Graphics.hpp>
#include <math.h>

class Player :
	public GameObject
{
public:
	Player();
	~Player();

	sf::Texture texture;
	sf::Sprite sprite;

	// The current velocity of the player (not in GameObject because they 
	// aren't really moving
	sf::Vector2<float> velocity;

	void update(float delta) override;
	void draw(sf::RenderWindow& window) override;


	const float LATERAL_ACCELERATION;
	const float MAX_LATERAL_SPEED;
	// The lateral boundaries that the player can't go past
	const int BOUNDS_LEFT;
	const int BOUNDS_RIGHT;

	const float DAMPENING_CONST;
};

