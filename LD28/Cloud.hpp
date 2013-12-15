#pragma once
#include "gameobject.hpp"
class Cloud :
	public GameObject
{
public:
	Cloud(void);
	~Cloud(void);

	sf::Texture texture;
	sf::Sprite sprite;

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;
};

