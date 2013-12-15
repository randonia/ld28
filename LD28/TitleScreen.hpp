#pragma once
#include "screen.hpp"
#include "GameScreen.hpp"

class TitleScreen :
	public Screen
{
public:
	TitleScreen(void);
	~TitleScreen(void);

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;
	void sendKey(sf::Keyboard::Key key) override;

};

