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
	mCollision->setCollisionType(CollisionFlags::SCORE);
}


Bonus::~Bonus(void)
{
}

void Bonus::update(float delta)
{
	GameObject::update(delta);
}

void Bonus::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
}