#pragma once

#ifndef __COLLISIONMODEL_H__
#define __COLLISIONMODEL_H__

#include <SFML\System\Vector2.hpp>
#include "GameObject.hpp"

struct CollisionModel
{
public:
	CollisionModel(void);
	CollisionModel(float rad);
	~CollisionModel(void);

	unsigned int collisionType;
	unsigned int collidesWith;

	// The radius of this shape (used for fast checking)
	float radius;
	// The parent gameobject
	GameObject* parent;

	void setCollisionType(CollisionFlags inFlags){ collisionType = collisionType | inFlags;}
	void setCollidesWith(CollisionFlags inFlags){ collidesWith = collidesWith | inFlags;}
	bool isColliding(CollisionModel& other);
	sf::CircleShape mCollisionDebug;

protected:
	// Had to put the friggin magnitude function here because apparently 
	// SFML vectors don't have the damn function
	// Calculates the magnitudeSquared of a vector
	float magSqr(sf::Vector2<float> vec);
	
	void setUpDebugCircle();
};

#endif