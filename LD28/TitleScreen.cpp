#include "TitleScreen.hpp"


TitleScreen::TitleScreen(void)
{
	std::cout << "Title Screen created!" << std::endl;
	// Load the texture
	if(!mMenuTexture.loadFromFile("assets/images/menu/titlescreen.png"))
	{
		std::cerr << "ERROR loading title screen menu asset." << std::endl;
	}

	mMenuSprite.setTexture(mMenuTexture);
	mMenuSprite.setOrigin(mMenuTexture.getSize().x * 0.5, 0.0f);
	mMenuSprite.setPosition(250.0f, 100.0f);
	
}


TitleScreen::~TitleScreen(void)
{
}

void TitleScreen::update(float delta)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		fRemoveScreen();
		GameScreen* screen = new GameScreen();
		fAddScreen(screen);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		HelpScreen* screen = new HelpScreen();
		// Don't forget to let it remove itself!
		screen->fRemoveScreen = fRemoveScreen;
		fAddScreen(screen);
	}
}

void TitleScreen::draw(sf::RenderTarget& window)
{
	window.draw(mMenuSprite);
}