#include "DeathParticle.hpp"
#include "CollisionModel.hpp"

DeathParticle::DeathParticle(float xDir, float yDir, float velocity)
{
	mID = "DeathParticle";
	// Load the texture
	if(!texture.loadFromFile("assets/images/deathparticle/deathparticle.png"))
	{
		std::cerr << "Error loading death particle texture" << std::endl;
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);
	}

	mCollision = new CollisionModel();
	mCollision->setCollisionType(CollisionFlags::NONE);
	mCollision->setCollidesWith(CollisionFlags::NONE);

	mDirection.x = xDir;
	mDirection.y = yDir;
	mVelocity = velocity;
}


DeathParticle::~DeathParticle(void)
{
}

void DeathParticle::update(float delta)
{
	GameObject::update(delta);
	position += mDirection * delta * mVelocity;
	sprite.setPosition(position);
}

void DeathParticle::draw(sf::RenderTarget& window)
{
	window.draw(sprite);
	GameObject::draw(window);
}