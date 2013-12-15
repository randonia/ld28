#include "Player.hpp"
#include "CollisionModel.hpp"

Player::Player() : LATERAL_ACCELERATION(500.0f), BOUNDS_LEFT(20), BOUNDS_RIGHT(500 - 20), 
	MAX_LATERAL_SPEED(250.0f), DAMPENING_CONST(0.75f), 
	mChuteState(ParachuteState::CLOSED), CHUTE_DEPLOY_TIME(1000.0f), CHUTE_LIFE_TIME(5000.0f), PARACHUTE_LATERAL_SPEED(100.0f)
{
	mID = "Player";
	// Load the texture
	if(!mFallTexture.loadFromFile("assets/images/player/player.png"))
	{
		std::cerr << "Error loading player falling texture" << std::endl;
	}
	else
	{
		sprite.setTexture(mFallTexture);
		sprite.setOrigin(mFallTexture.getSize().x * 0.5f, mFallTexture.getSize().y * 0.5f);
	}
	// Load the other textures but don't use them yet
	if(!mDeployingTexture.loadFromFile("assets/images/player/player_chute_deploying.png"))
	{
		std::cerr << "Error loading player deploying texture" << std::endl;
	}
	if(!mOpenTexture.loadFromFile("assets/images/player/player_chute_open.png"))
	{
		std::cerr << "Error loading player open chute texture" << std::endl;
	}
	if(!mBonedTexture.loadFromFile("assets/images/player/player_chute_gone.png"))
	{
		std::cerr << "Error loading player boned texture texture" << std::endl;
	}
	
	mCollision = new CollisionModel(10.0f);
	mCollision->parent = this;
	mCollision->setCollidesWith(CollisionFlags::OBSTACLE | CollisionFlags::SCORE);
	mCollision->setCollisionType(CollisionFlags::PLAYER);
}


Player::~Player(void)
{
}

void Player::update(float delta)
{
	GameObject::update(delta);

	switch (mChuteState)
	{
	case CLOSED:
		chuteClosedTick(delta);
		break;
	case DEPLOYING:
		chuteDeployingTick(delta);
		break;
	case OPEN:
		chuteOpenTick(delta);
		break;
	case BONED:
		chuteBonedTick(delta);
		break;
	default:
		break;
	}
	
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

void Player::chuteClosedTick(float delta)
{
	bool skipDampening = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		velocity.x -= LATERAL_ACCELERATION * delta;
		sprite.setScale(-1.0f,1.0f);
		skipDampening = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		velocity.x += LATERAL_ACCELERATION * delta;
		sprite.setScale(1.0f,1.0f);
		skipDampening = true;
	}
	// Deploy the chute if the player hits space
	if(mChuteState == ParachuteState::CLOSED && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		std::cout << "Deploying chute!" << std::endl;
		mChuteState = ParachuteState::DEPLOYING;

		// Change the texture out
		sprite.setTexture(mDeployingTexture,true);
		sprite.setOrigin(16.0f, 48.0f);

		// Start the clock
		mChuteTimer.restart();
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

}

void Player::chuteDeployingTick(float delta)
{
	// Move the player while they're deploying.
	position.y += 50.0f * delta;
	if(mChuteTimer.getElapsedTime().asMilliseconds() > CHUTE_DEPLOY_TIME)
	{
		mChuteState = ParachuteState::OPEN;
		sprite.setTexture(mOpenTexture, true);
		sprite.setOrigin(16.0f, 48.0f);
	}
}

void Player::chuteOpenTick(float delta)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		position.x -= PARACHUTE_LATERAL_SPEED * delta;
		sprite.setScale(-1.0f,1.0f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		position.x += PARACHUTE_LATERAL_SPEED * delta;
		sprite.setScale(1.0f,1.0f);
	}

}

void Player::chuteBonedTick(float delta)
{

}

void Player::draw(sf::RenderTarget& window)
{
	// Draw the sprite
	window.draw(sprite);

	// Draw the base for debugging
	GameObject::draw(window);
}