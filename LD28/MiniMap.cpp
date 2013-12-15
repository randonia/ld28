#include "MiniMap.hpp"

MiniMap::MiniMap() : mMapBG(), mMapFG(), mMarkerRect(sf::Vector2f(100.0f, 10.0f))
{
	mMarkerRect.setFillColor(sf::Color::Blue);
	mMarkerRect.setOutlineColor(sf::Color::Black);

	if(!mMapBG.create(500,700))
	{
		std::cerr << "MiniMap background failed to create! Oh no" << std::endl;
	}
	if(!mMapFG.create(100,700))
	{
		std::cerr << "MiniMap foreground failed to create! Oh no" << std::endl;
	}

	mSpriteMapBG.setTexture(mMapBG.getTexture());
	mSpriteMapBG.setPosition(400.0f, 0.0f);
	mSpriteMapFG.setTexture(mMapFG.getTexture());
	mSpriteMapFG.setPosition(400.0f, 0.0f);
}

MiniMap::~MiniMap(void)
{
}

void MiniMap::preDrawObjects(std::vector<GameObject*> renderings)
{

}

void MiniMap::updateMarker(float percentComplete)
{
	mMarkerRect.setPosition(0.0f, percentComplete * 700.0f);
}

void MiniMap::draw(sf::RenderTarget& target)
{
	mMapFG.clear(sf::Color::Transparent);
	mMapFG.draw(mMarkerRect);
	mMapFG.display();
	target.draw(mSpriteMapBG);
	target.draw(mSpriteMapFG);
}