#include "Obstacle.hpp"
#include "CollisionModel.hpp"


Obstacle::Obstacle(void)
{
	mID = "Obstacle";
	// Load the texture
	if(!texture.loadFromFile("assets/images/obstacle/obstacle.png"))
	{
		std::cerr << "Error loading obstacle texture" << std::endl;
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);
	}

	mCollision = new CollisionModel(25.0f);
	mCollision->parent = this;
	mCollision->setCollidesWith(CollisionFlags::PLAYER);
	mCollision->setCollisionType(CollisionFlags::OBSTACLE);
}


Obstacle::~Obstacle(void)
{
}

void Obstacle::update(float delta)
{
	GameObject::update(delta);
	sprite.setPosition(position);
};

void Obstacle::draw(sf::RenderTarget& window)
{
	window.draw(sprite);

	GameObject::draw(window);
}