#pragma once
#include "Screen.hpp"
class HighScoreScreen :
	public Screen
{
public:
	HighScoreScreen(int score);
	~HighScoreScreen(void);

	int mScore;

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;

	sf::Font mFontUbuntu;
	sf::Text mDisplayText;

	sf::Texture mScoreTexture;
	sf::Sprite mSprite;

	sf::Music mBGM;
};

