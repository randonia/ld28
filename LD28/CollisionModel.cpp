#include "CollisionModel.hpp"

CollisionModel::CollisionModel(void) : collidesWith(0x0), collisionType(0x0)
{
	radius = 0;
	setUpDebugCircle();
}

CollisionModel::CollisionModel(float rad) : collidesWith(0x0), collisionType(0x0)
{
	this->radius = rad;
	setUpDebugCircle();
}

CollisionModel::~CollisionModel(void)
{
}

void CollisionModel::setUpDebugCircle()
{
	mCollisionDebug = sf::CircleShape(radius);
	mCollisionDebug.setOrigin(radius, radius);
	mCollisionDebug.setFillColor(sf::Color::Transparent);
	mCollisionDebug.setOutlineColor(sf::Color::Red);
	mCollisionDebug.setOutlineThickness(1.0f);
}

bool CollisionModel::isColliding(CollisionModel& other)
{
	// Do a radius check to make sure they should collide
	return magSqr(parent->position - other.parent->position) < (radius * radius + other.radius * other.radius);
}

float CollisionModel::magSqr(sf::Vector2<float> vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}