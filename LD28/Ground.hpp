#pragma once
#include "gameobject.hpp"
// The ground is the end of the level. If the player hits the ground 
// with a parachute active, They save their score and end the run.
// If they hit the ground with no parachute active, they die.
class Ground :
	public GameObject
{
public:
	Ground(void);
	~Ground(void);

	sf::Texture texture;
	sf::Sprite sprite;

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;

};

