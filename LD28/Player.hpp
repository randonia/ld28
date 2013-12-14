#pragma once
#include "gameobject.hpp"
#include <SFML\Graphics.hpp>
class Player :
	public GameObject
{
public:
	Player(void);
	~Player(void);

	sf::Texture texture;
	sf::Sprite sprite;

	void update(sf::Time delta) override;
	void draw(sf::RenderWindow& window) override;
};

