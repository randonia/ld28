#include "Player.hpp"
#include "CollisionModel.hpp"

Player::Player() : LATERAL_ACCELERATION(500.0f), VERTICAL_ACCELERATION(150.0f),
	MAX_LATERAL_SPEED(250.0f), MAX_VERTICAL_SPEED(100.0f), DAMPENING_CONST(0.75f), 
	mRenderingEnabled(true),
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
	mCollision->setCollidesWith(CollisionFlags::OBSTACLE | CollisionFlags::SCORE | CollisionFlags::GROUND);
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
	
	// I had to move the bounce check outside of Player and into GameScreen::update.
	// ... because of reasons....

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
	// Do lots of dampening on the up/down velocity
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y += VERTICAL_ACCELERATION * delta;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y -= VERTICAL_ACCELERATION * delta;
	}
	else
	{
		velocity.y = pow((0.15), delta) * velocity.y;
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
	if(velocity.y <= -MAX_VERTICAL_SPEED)
	{
		velocity.y = -MAX_VERTICAL_SPEED;
	}
	if(velocity.y >= MAX_VERTICAL_SPEED)
	{
		velocity.y = MAX_VERTICAL_SPEED;
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
		// Restart the timer
		mChuteTimer.restart();
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		position.y += 15.0f * delta;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		position.y -= 15.0f * delta;
	}

	// See if it's time to ruin the player's day.
	if(mChuteTimer.getElapsedTime().asMilliseconds() > CHUTE_LIFE_TIME)
	{
		mChuteState = ParachuteState::BONED;
		// Change the textures
		sprite.setTexture(mBonedTexture, true);
		sprite.setOrigin(16.0f, 16.0f);
	}
}

void Player::chuteBonedTick(float delta)
{

}

void Player::reset()
{
	// Resets the player to default settings. Actually pretty simple
	mChuteState = ParachuteState::CLOSED;
	sprite.setTexture(mFallTexture, true);
	sprite.setOrigin(16.0f,16.0f);
	position = sf::Vector2<float>(position.x ,0.0f);
	velocity = sf::Vector2<float>(velocity.x ,0.0f);
	mRenderingEnabled = true;
}

void Player::draw(sf::RenderTarget& window)
{
	// Draw the sprite
	if(mRenderingEnabled)
	{
		window.draw(sprite);
	}

	// Draw the base for debugging
	GameObject::draw(window);
}