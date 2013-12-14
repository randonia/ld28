#include "Player.hpp"
#include "CollisionModel.hpp"

Player::Player() : LATERALSPEED(150.0f), BOUNDS_LEFT(20), BOUNDS_RIGHT(500 - 20), 
	MAX_LATERAL_SPEED(250.0f), DAMPENING_CONST(0.65f)
{
	mID = "Player";
	// Load the texture
	if(!texture.loadFromFile("assets/images/player/player.png"))
	{
		std::cerr << "Error loading player texture" << std::endl;
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);
	}
	
	mCollision = new CollisionModel(10.0f);
	mCollision->setCollisionType(CollisionFlags::PLAYER);
}


Player::~Player(void)
{
}

void Player::update(float delta)
{
	GameObject::update(delta);

	bool skipDampening = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		velocity.x -= LATERALSPEED * delta;
		sprite.setScale(-1.0f,1.0f);
		skipDampening = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		velocity.x += LATERALSPEED * delta;
		sprite.setScale(1.0f,1.0f);
		skipDampening = true;
	}
	// Speed checks
	if(velocity.x <= -MAX_LATERAL_SPEED)
	{
		velocity.x = -MAX_LATERAL_SPEED;
	}
	if(velocity.x >= MAX_LATERAL_SPEED)
	{
		velocity.x = MAX_LATERAL_SPEED;
	}

	// Apply dampening if it should be (based on keyboard input)
	if(!skipDampening)
	{
		//velocity.x = (1 - DAMPENING_CONST * delta) * velocity.x;
		velocity.x = pow((1 - DAMPENING_CONST),delta) * velocity.x;
	}

	position += velocity * delta;

	// Do a bounce check
	if(position.x <= BOUNDS_LEFT)
	{
		// Bounce
		velocity.x *= -1;
		// and move them a bit
		position.x = BOUNDS_LEFT;
	}
	if(position.x >= BOUNDS_RIGHT)
	{
		velocity.x *= -1;
		position.x = BOUNDS_RIGHT;
	}

	// Move the sprite to the location of this player
	sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow& window)
{
	// Draw the sprite
	window.draw(sprite);

	// Draw the base for debugging
	GameObject::draw(window);
}