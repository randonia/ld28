#pragma once
#include "gameobject.hpp"
#include <SFML\Graphics.hpp>
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

	const float GRAVITY;
	const float MAX_FALL_VELOCITY;
};

