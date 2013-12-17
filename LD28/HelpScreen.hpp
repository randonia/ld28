#pragma once
#include "Screen.hpp"
class HelpScreen :
	public Screen
{
public:
	HelpScreen(void);
	~HelpScreen(void);
	
	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;

	sf::Texture mHelp1;
	sf::Texture mHelp2;
	sf::Sprite mMenuSprite;

	bool mLeftReleased;
	bool mRightReleased;

	int mCurrHelpFrame;
};

