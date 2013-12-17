#pragma once
#include "GameObject.hpp"
class Obstacle :
	public GameObject
{
public:
	Obstacle(void);
	~Obstacle(void);

	sf::Texture texture;
	sf::Sprite sprite;

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;
};

