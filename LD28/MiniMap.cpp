#include "MiniMap.hpp"

MiniMap::MiniMap() : mMapBG(), mMapFG(), mMarkerRect(sf::Vector2f(100.0f, 10.0f))
{
	mMarkerRect.setFillColor(sf::Color::Blue);
	mMarkerRect.setOutlineColor(sf::Color::Black);

	if(!mMapBG.create(50,700))
	{
		std::cerr << "MiniMap background failed to create! Oh no" << std::endl;
	}
	if(!mMapFG.create(50,700))
	{
		std::cerr << "MiniMap foreground failed to create! Oh no" << std::endl;
	}
	// Load the temporary texture to avoid ugly
	if(!mTextureBackground.loadFromFile("assets/images/hud/minimap.png"))
	{
		std::cerr << "Minimap background texture not loaded! Missing asset" << std::endl;
	}

	//mSpriteMapBG.setTexture(mMapBG.getTexture());
	mSpriteMapBG.setTexture(mTextureBackground);
	mSpriteMapBG.setPosition(450.0f, 0.0f);
	mSpriteMapFG.setTexture(mMapFG.getTexture());
	mSpriteMapFG.setPosition(450.0f, 0.0f);

}

MiniMap::~MiniMap(void)
{
}

void MiniMap::preDrawObjects(std::vector<GameObject*> renderings)
{
	// The marker is what displays the dots for the map. Move it around
	// to draw the objects. Change its colors based on the object type
	sf::CircleShape marker(5.0f);
	marker.setOutlineThickness(1.0f);

	for(std::vector<GameObject*>::iterator renderator = renderings.begin();
		renderator != renderings.end();
		++renderator)
	{
		// Check its type to see what it is and how we should set up the colors
		if((*renderator)->checkCollisionType(CollisionFlags::SCORE))
		{
			marker.setRadius(2.0f);
			marker.setOrigin(2.0f,2.0f);
			marker.setFillColor(sf::Color::Cyan);
			marker.setOutlineColor(sf::Color::Blue);
		} 
		else if((*renderator)->checkCollisionType(CollisionFlags::OBSTACLE))
		{
			marker.setRadius(3.0f);
			marker.setOrigin(3.0f,3.0f);
			marker.setFillColor(sf::Color::Red);
			marker.setOutlineColor(sf::Color::Black);
		}
		else
		{
			// Don't draw something if it isn't a SCORE or OBSTACLE
			continue;
		}

		// Map it to the position on the rendertarget
		float xMapped = mapPoint((*renderator)->position.x, 400.0f,100.0f);
		float yMapped = mapPoint((*renderator)->position.y, mDistance, 700.0f);
		std::cout << "Drawing: " << (*renderator)->mID << " " << (*renderator)->position.x << ":" << (*renderator)->position.y << " mapped to: " << xMapped << "," << yMapped << std::endl;
		marker.setPosition(xMapped, yMapped);
		mMapBG.draw(marker);
	}
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