#include "Player.hpp"


Player::Player(void)
{
	// Load the texture
	if(!texture.loadFromFile("assets/images/player/player.png"))
	{
		std::cerr << "Error loading player texture" << std::endl;
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x * 0.5, texture.getSize().y * 0.5);
	}
}


Player::~Player(void)
{
}

void Player::update(sf::Time delta)
{
	GameObject::update(delta);

	// Be affected by gravity

	// Move the sprite to the location of this player
	sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow& window)
{
	// Draw the sprite
	window.draw(sprite);
	window.draw(center);
}