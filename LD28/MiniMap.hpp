#pragma once

#include <SFML\Graphics.hpp>
#include "GameObject.hpp"

/* The MiniMap will draw a rendertexture of a line showing your
 * current position, the goal, and *possibly* the other gameobjects.
 */
class MiniMap
{
public:
	MiniMap();
	~MiniMap(void);

	void preDrawObjects(std::vector<GameObject*> renderings);

	void updateMarker(float percentComplete);
	void draw(sf::RenderTarget& target);

	float mDistance;

private:
	
	// The rendertexture and associated sprites
	sf::Sprite mSpriteMapBG;
	sf::Sprite mSpriteMapFG;
	sf::RenderTexture mMapBG;
	sf::RenderTexture mMapFG;

	// The rectangle to draw on the rendertexture
	sf::RectangleShape mMarkerRect;
};
