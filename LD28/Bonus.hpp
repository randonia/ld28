#pragma once
#include "gameobject.hpp"

// The bonus object is the thing that gives you points
class Bonus : public GameObject
{
public:
	Bonus(void);
	~Bonus(void);

	sf::Texture texture;
	sf::Sprite sprite;

	void update(float delta) override;
	void draw(sf::RenderWindow& window) override;

};

