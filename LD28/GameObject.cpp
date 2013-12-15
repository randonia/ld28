#include "GameObject.hpp"
#include "CollisionModel.hpp"

GameObject::GameObject(void)
{
	// Set up the default shape
	center = sf::CircleShape(2);
	center.setOrigin(center.getRadius(), center.getRadius());
	center.setFillColor(sf::Color::Red);
	center.setOutlineColor(sf::Color::Cyan);
	center.setOutlineThickness(1);
	mID = "EmptyGameObject";
	position = sf::Vector2<float>(50,50);
	
	// Set up the collision model
	const float RADIUS = 15.0f;
	mCollision = new CollisionModel(RADIUS);
}


GameObject::~GameObject(void)
{
}

unsigned int GameObject::getCollisionType()
{
	return mCollision->collisionType;
}

bool GameObject::checkCollisionType(unsigned int flagToCheck)
{
	return ((mCollision->collisionType & flagToCheck) == flagToCheck);
}

unsigned int GameObject::getCollidesWith()
{
	return mCollision->collidesWith;
}

bool GameObject::checkCollidesWith(unsigned int flagToCheck)
{
	return (flagToCheck != CollisionFlags::NONE) && ((mCollision->collidesWith & flagToCheck) == flagToCheck);
}


void GameObject::update(float delta)
{
	center.setPosition(position);
	mCollision->mCollisionDebug.setPosition(position);
}

void GameObject::draw(sf::RenderTarget& window)
{
	window.draw(center);
	window.draw(mCollision->mCollisionDebug);
}