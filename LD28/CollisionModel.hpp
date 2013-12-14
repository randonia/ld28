#pragma once

#ifndef __COLLISIONMODEL_H__
#define __COLLISIONMODEL_H__

#include <SFML\System\Vector2.hpp>
#include "GameObject.hpp"

enum CollisionFlags : unsigned int
{
	NONE = 0,
	PLAYER = 1,
	SCORE = 2,
	OBSTACLE = 3
};

struct CollisionModel
{
public:
	CollisionModel(void);
	~CollisionModel(void);

	CollisionFlags collisionType;
	CollisionFlags collidesWith;

	// The radius of this shape (used for fast checking)
	float radius;
	// The parent gameobject
	GameObject* parent;
	
	bool isColliding(CollisionModel& other);
protected:
	// Had to put the friggin magnitude function here because apparently 
	// SFML vectors don't have the damn function
	// Calculates the magnitudeSquared of a vector
	float magSqr(sf::Vector2<float> vec);
};

#endif