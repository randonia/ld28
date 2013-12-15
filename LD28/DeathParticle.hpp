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

	// Used to calculate when to stop displaying this particle
	sf::Clock mStopDisplayTimer;
	// How long to display the particle. 1.5 seconds + rand
	float DISPLAY_LENGTH;

	void update(float delta) override;
	void draw(sf::RenderTarget& window) override;

	// Basically the Y accelerator
	float mDropSpeed;
	float mRot;
};

