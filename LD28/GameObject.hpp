#pragma once

#include <string>
#include <iostream>
#include <SFML\System\Vector2.hpp>

#include "CollisionModel.hpp"

class GameObject
{
public:
	GameObject(void);
	virtual ~GameObject(void);
	sf::Vector2<float> position;
	
	
protected:
	std::string mID;
	CollisionModel mCollision;
};

