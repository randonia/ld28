#pragma once

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <iostream>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics.hpp>

// For forward declaration issue :/
struct CollisionModel;

enum CollisionFlags : unsigned int
{
	NONE = 0,
	PLAYER = 1,
	SCORE = 2,
	OBSTACLE = 3
};

class GameObject
{
public:
	GameObject(void);
	virtual ~GameObject(void);

	// The position of this object. Center origin!
	sf::Vector2<float> position;

	virtual void update(float delta);
	virtual void draw(sf::RenderWindow& window);
	
	CollisionFlags getCollisionFlags();
	// Returns true if the given flag exists
	bool checkCollisionFlags(CollisionFlags flagToCheck);

protected:
	// The debug id
	std::string mID;
	// The CollisionModel this gameobject uses
	CollisionModel * mCollision;
	
	// The shape to draw to the renderwindow
	sf::CircleShape center;
};

#endif