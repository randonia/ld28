#pragma once
#include "gameobject.hpp"

// The death particle is basically the Mega Man particle when he dies
class DeathParticle :
	public GameObject
{
public:
	DeathParticle(float xDir, float yDir, float velocity);
	~DeathParticle(void);

	// The velocity of this particle's movement
	float mVelocity;
	// This should be normalized.
	sf::Vector2<float> mDirection;

	sf::Texture texture;
	sf::Sprite sprite;

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;
};

