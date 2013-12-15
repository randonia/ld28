#include "Cloud.hpp"
#include "CollisionModel.hpp"

Cloud::Cloud(void)
{
	mID = "Cloud";
	// Load the texture
	if(!texture.loadFromFile("assets/images/clouds/cloud1.png"))
	{
		std::cerr << "Error loading cloud texture" << std::endl;
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);
	}

	mCollision = new CollisionModel();
	mCollision->setCollidesWith(CollisionFlags::NONE);
	mCollision->setCollisionType(CollisionFlags::NONE);
}


Cloud::~Cloud(void)
{
}

void Cloud::update(float delta)
{
	GameObject::update(delta);
	sprite.setPosition(position);
}

void Cloud::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}