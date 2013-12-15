#include "HelpScreen.hpp"


HelpScreen::HelpScreen(void) : mCurrHelpFrame(0), mLeftReleased(false), mRightReleased(false)
{
	std::cout << "Title Screen created!" << std::endl;
	// Load the texture
	if(!mHelp1.loadFromFile("assets/images/menu/helpmenu1.png"))
	{
		std::cerr << "ERROR loading help screen #1 menu asset." << std::endl;
	}
	if(!mHelp2.loadFromFile("assets/images/menu/helpmenu2.png"))
	{
		std::cerr << "ERROR loading help screen #2 menu asset." << std::endl;
	}

	mMenuSprite.setTexture(mHelp1);
	mMenuSprite.setOrigin(mHelp1.getSize().x * 0.5, 0.0f);
	mMenuSprite.setPosition(250.0f, 100.0f);
}


HelpScreen::~HelpScreen(void)
{
}

void HelpScreen::update(float delta)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if(mRightReleased && mCurrHelpFrame == 0)
		{
			mMenuSprite.setTexture(mHelp2);
			mRightReleased = false;
			mCurrHelpFrame = 1;
		}
	}
	else
	{
		mRightReleased = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(mLeftReleased && mCurrHelpFrame == 1)
		{
			mMenuSprite.setTexture(mHelp1);
			mLeftReleased = false;
			mCurrHelpFrame = 0;
		}
	}
	else
	{
		mLeftReleased = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		// Remove this screen
		fRemoveScreen();
	}
}

void HelpScreen::draw(sf::RenderTarget& window)
{
	window.draw(mMenuSprite);
}