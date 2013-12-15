#include "TitleScreen.hpp"


TitleScreen::TitleScreen(void)
{
	std::cout << "Title Screen created!" << std::endl;
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
}

void TitleScreen::draw(sf::RenderTarget& window)
{

}

void TitleScreen::sendKey(sf::Keyboard::Key key)
{

}