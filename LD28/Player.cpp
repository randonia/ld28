#include "Player.hpp"

Player::Player() : GRAVITY(9.8f), MAX_FALL_VELOCITY(10.0f)
{
	// Load the texture
	if(!texture.loadFromFile("assets/images/player/player.png"))
	{
		std::cerr << "Error loading player texture" << std::endl;
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);
	}
}


Player::~Player(void)
{
}

void Player::update(float delta)
{
	GameObject::update(delta);

	// Be affected by gravity
	velocity.y += delta * GRAVITY;
	if(velocity.y >= MAX_FALL_VELOCITY)
	{
		velocity.y = MAX_FALL_VELOCITY;
	}

	position += velocity;

	// Move the sprite to the location of this player
	sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow& window)
{
	// Draw the sprite
	window.draw(sprite);
	window.draw(center);
}