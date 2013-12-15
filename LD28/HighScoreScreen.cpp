#include "HighScoreScreen.hpp"


HighScoreScreen::HighScoreScreen(float score) : mFontUbuntu(), mDisplayText("Hooray", mFontUbuntu)
{
	mScore = score;
	// Initialize the texture
	if(!mScoreTexture.loadFromFile("assets/images/menu/highscorebg.png"))
	{
		std::cerr << "The high score asset was missing from this" << std::endl;
	}

	mSprite.setTexture(mScoreTexture);
	mSprite.setOrigin(mScoreTexture.getSize().x * 0.5, 0.0f);
	mSprite.setPosition(250.0f, 0.0f);

	mFontUbuntu.loadFromFile("assets/fonts/UbuntuMono.ttf");
	mDisplayText.setCharacterSize(24);
	mDisplayText.setStyle(sf::Text::Regular);
	mDisplayText.setColor(sf::Color::White);
	mDisplayText.setPosition(250.0f,170.0f);
	mDisplayText.setString(std::to_string((int)mScore));
	mDisplayText.setOrigin(mDisplayText.getLocalBounds().width * 0.5, mDisplayText.getLocalBounds().height * 0.5);
	
}


HighScoreScreen::~HighScoreScreen(void)
{
}

void HighScoreScreen::update(float delta)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		fRemoveScreen();
	}
}

void HighScoreScreen::draw(sf::RenderTarget& window)
{
	window.draw(mSprite);
	// My attempt at a shadow
	window.draw(mDisplayText);
	mDisplayText.setPosition(249.0f, 169.0f);
	mDisplayText.setColor(sf::Color::White);
	window.draw(mDisplayText);
	mDisplayText.setPosition(250.0f, 170.0f);
	mDisplayText.setColor(sf::Color::Black);
}
