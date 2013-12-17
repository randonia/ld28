#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

/* The MiniMap will draw a rendertexture of a line showing your
 * current position, the goal, and *possibly* the other gameobjects.
 */
class MiniMap
{
public:
	MiniMap();
	~MiniMap(void);

	/*
	 * This will basically draw EVERY renderable game object once
	 * and then keep that texture around forever.
	 * Also it will squish it down so it fits
	 */
	void preDrawObjects(std::vector<GameObject*> renderings);

	void updateMarker(float percentComplete);
	void draw(sf::RenderTarget& target);

	void reset();

	// The maximum distance (y-wise) an object is
	float mDistance;

private:
	
	// The rendertexture and associated sprites
	sf::Sprite mSpriteMapBG;
	sf::Sprite mSpriteMapFG;
	sf::RenderTexture mMapBG;
	sf::RenderTexture mMapFG;
	sf::Texture mTextureBackground;

	// The rectangle to draw on the rendertexture
	sf::RectangleShape mMarkerRect;

	// Takes a point on one size and changes it to be the same (relative)
	// point on a different size.
	// Example: You have a 10x10 grid and you have point (5,5), what is that
	// point mapped down to a 5x5 grid? Answer: (2.5,2.5)
	// NO VALIDATION USED! WILL NOT PROTECT AGAINST BAD INPUT
	float mapPoint(float value, float scaleStart, float scaleEnd){ return (value * scaleEnd / scaleStart);};
	float mapPoint(int value, int scaleStart, int scaleEnd){return mapPoint((float)value, (float)scaleStart, (float)scaleEnd);};
};
