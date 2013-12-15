#include "Ground.hpp"
#include "CollisionModel.hpp"

Ground::Ground(void)
{
	mID = "Ground";
	// Load the texture
	if(!texture.loadFromFile("assets/images/ground/ground.png"))
	{
		std::cerr << "Error loading ground texture" << std::endl;
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x * 0.5f, 16.0f);
	}
	
	mCollision = new CollisionModel(20.0f);
	mCollision->parent = this;
	mCollision->setCollidesWith(CollisionFlags::PLAYER);
	mCollision->setCollisionType(CollisionFlags::GROUND);
}

Ground::~Ground(void)
{
}

void Ground::update(float delta)
{
	GameObject::update(delta);
	sprite.setPosition(position);
}

void Ground::draw(sf::RenderTarget& window)
{
	window.draw(sprite);

	GameObject::draw(window);
}