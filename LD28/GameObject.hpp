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
	OBSTACLE = 4
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
	
	// Use this to grab the flag this collides with
	unsigned int getCollidesWith();
	// Returns true if the given flag exists. Use this to test what this collides with
	bool checkCollidesWith(unsigned int flagToCheck);

	// Use this to identify this gameobject's flags
	unsigned int getCollisionType();
	// Returns true if the given flag to check matches this gameobject's type
	bool checkCollisionType(unsigned int flagToCheck);
	

	// The CollisionModel this gameobject uses
	CollisionModel * mCollision;
	
	// The name (not the ID) of this object
	std::string name;

protected:
	// The debug id
	std::string mID;

	// The shape to draw to the renderwindow
	sf::CircleShape center;
};

// A collision info data holder. Gets pushed when a collision occurs
struct CollisionInfo
{
public:

	CollisionInfo(GameObject* src, GameObject* trg)
	{
		source = src;
		target = trg;
	}
	~CollisionInfo()
	{
		
	}

	GameObject* source;
	GameObject* target;
};

#endif