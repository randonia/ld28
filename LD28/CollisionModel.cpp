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
	return ((collidesWith & other.collisionType) != 0) && 
}