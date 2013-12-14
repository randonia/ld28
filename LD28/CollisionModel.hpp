#pragma once
#include <SFML\System\Vector2.hpp>
#include "GameObject.hpp"

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
	
};

enum CollisionFlags : unsigned int
{
	NONE = 0,
	PLAYER = 1,
	SCORE = 2,
	OBSTACLE = 3
};
