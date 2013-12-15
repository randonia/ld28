#pragma once
#include "screen.hpp"
class HighScoreScreen :
	public Screen
{
public:
	HighScoreScreen(float score);
	~HighScoreScreen(void);

	float mScore;

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;

	sf::Font mFontUbuntu;
	sf::Text mDisplayText;

	sf::Texture mScoreTexture;
	sf::Sprite mSprite;

	sf::Music mBGM;
};

