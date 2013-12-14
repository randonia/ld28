#include "GameObject.hpp"
#include "CollisionModel.hpp"

GameObject::GameObject(void)
{
	// Set up the default shape
	center = sf::CircleShape(2);
	center.setOrigin(center.getRadius() * 0.5, center.getRadius() * 0.5);
	center.setFillColor(sf::Color::Red);
	center.setOutlineColor(sf::Color::Cyan);
	center.setOutlineThickness(1);
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