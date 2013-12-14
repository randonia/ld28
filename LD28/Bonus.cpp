#include "Bonus.hpp"
#include "CollisionModel.hpp"


Bonus::Bonus(void)
{
	mID = "Bonus";
	// Load the texture
	if(!texture.loadFromFile("assets/images/bonus/bonus.png"))
	{
		std::cerr << "Error loading bonus texture" << std::endl;
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);
	}

	// Set up the collision data
	mCollision = new CollisionModel(10.0f);
	mCollision->parent = this;
	mCollision->setCollisionType(CollisionFlags::SCORE);
}


Bonus::~Bonus(void)
{
}

void Bonus::update(float delta)
{
	GameObject::update(delta);
	sprite.setPosition(position);
}

void Bonus::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	GameObject::draw(window);
}