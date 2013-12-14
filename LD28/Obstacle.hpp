#pragma once
#include "gameobject.hpp"
class Obstacle :
	public GameObject
{
public:
	Obstacle(void);
	~Obstacle(void);

	sf::Texture texture;
	sf::Sprite sprite;

	void update(float delta) override;
	void draw(sf::RenderWindow& window) override;
};

