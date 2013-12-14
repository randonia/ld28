#include "Player.hpp"
#include "CollisionModel.hpp"

Player::Player() : LATERALSPEED(0.25f)
{
	mID = "Player";
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
	
	mCollision = new CollisionModel(10.0f);
	mCollision->setCollisionType(CollisionFlags::PLAYER);
}


Player::~Player(void)
{
}

void Player::update(float delta)
{
	GameObject::update(delta);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		velocity.x -= LATERALSPEED;
		sprite.setScale(-1.0f,1.0f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		velocity.x += LATERALSPEED;
		sprite.setScale(1.0f,1.0f);
	}

	position += velocity * delta;

	// Move the sprite to the location of this player
	sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow& window)
{
	// Draw the sprite
	window.draw(sprite);

	// Draw the base for debugging
	GameObject::draw(window);
}