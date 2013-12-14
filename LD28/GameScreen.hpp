#pragma once

#include "Screen.hpp"
#include "GameObject.hpp"
#include "Player.hpp"

class GameScreen : public Screen
{
public:
	GameScreen(void);
	~GameScreen(void);

	std::vector<GameObject*> mGameObjects;

	Player * player;

	void update(float delta) override;
	void draw(sf::RenderWindow& window) override;
};

