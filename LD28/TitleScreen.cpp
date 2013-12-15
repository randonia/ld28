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
	
	if(!mBGMusic.openFromFile("assets/audio/bgmenu.ogg"))
	{
		std::cerr << "Unable to load the menu background track" << std::endl;
	}
	mBGMusic.play();
	
}


TitleScreen::~TitleScreen(void)
{
}

void TitleScreen::update(float delta)
{
	// Play the music if it isn't
	if(mBGMusic.getStatus() != sf::Music::Playing)
	{
		mBGMusic.play();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		GameScreen* screen = new GameScreen();
		screen->fAddScreen = fAddScreen;
		screen->fRemoveScreen = fRemoveScreen;
		fAddScreen(screen);
		mBGMusic.stop();
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