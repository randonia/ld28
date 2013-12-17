#pragma once
#include "Screen.hpp"
#include "GameScreen.hpp"
#include "HelpScreen.hpp"

class TitleScreen :
	public Screen
{
public:
	TitleScreen(void);
	~TitleScreen(void);

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;

	sf::Texture mMenuTexture;
	sf::Sprite mMenuSprite;

	sf::Music mBGMusic;
};

