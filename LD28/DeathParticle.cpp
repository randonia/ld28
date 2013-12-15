#include "DeathParticle.hpp"
#include "CollisionModel.hpp"

DeathParticle::DeathParticle(float xDir, float yDir, float velocity) : DISPLAY_LENGTH(500.0f)
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

	mDirection.x = xDir + (rand() % 10 - 5);
	mDirection.y = yDir;
	mVelocity = velocity;

	mStopDisplayTimer.restart();
	DISPLAY_LENGTH += rand() % 1000;
}


DeathParticle::~DeathParticle(void)
{
}

void DeathParticle::update(float delta)
{
	GameObject::update(delta);
	mDirection.y += (5.0f + ((rand() % 100) / 100)) * delta;
	position += mDirection * delta * mVelocity;
	sprite.setPosition(position);
}

void DeathParticle::draw(sf::RenderTarget& window)
{
	if(mStopDisplayTimer.getElapsedTime().asMilliseconds() < DISPLAY_LENGTH)
	{
		window.draw(sprite);
	}
	else if(mStopDisplayTimer.getElapsedTime().asMilliseconds() < DISPLAY_LENGTH * 2.0f)
	{
		window.draw(center);
	}
	GameObject::draw(window);
}