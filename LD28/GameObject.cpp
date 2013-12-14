#include "GameObject.hpp"
#include "CollisionModel.hpp"

GameObject::GameObject(void)
{
	// Set up the default shape
	center = sf::CircleShape(1);
	mID = "EmptyGameObject";
	position = sf::Vector2<float>(50,50);
}


GameObject::~GameObject(void)
{
}

void GameObject::update(sf::Time delta)
{
	center.setPosition(position);
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(center);
}