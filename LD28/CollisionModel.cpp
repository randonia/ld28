#include "CollisionModel.hpp"

CollisionModel::CollisionModel(void)
{
	radius = 0;
}


CollisionModel::~CollisionModel(void)
{
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