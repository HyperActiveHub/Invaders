#include "ShipEntity.h"
#include "BulletEntity.h"
#include "ExplosionEntity.h"

namespace
{
	const float RADIUS = 30.0f; //placeholder
	const float FIRE_DELTA = 0.5f;
	const float VELOCITY = 300.0f;
}

ShipEntity::ShipEntity(Game* game, Vector2f position) :
	Entity(game, "Ship.psd", position, RADIUS, EntityType::SHIP, EntityFaction::FRIEND),
	mFireDelta(FIRE_DELTA),
	mFireTime(0.0f),
	mVelocity(VELOCITY),
	mFirePwr(1),
	mBulletDirs(1, Vector2f(0, -1))
{
	std::cout << "Hello Ship." << std::endl;
}

ShipEntity::~ShipEntity()
{
	std::cout << "Goodbye Ship." << std::endl;
}

void ShipEntity::update(float deltaTime)
{
	Vector2f inputVector = input();
	constrainPosition(inputVector);
	handleMovement(inputVector, deltaTime);
	handleFire(deltaTime);

	Entity::update(deltaTime);
}

void ShipEntity::collide(Entity* other)
{
	//game over?
	//string str = typeid(*other).name();
	//str.replace(0, 6, "");	//remove "class" from type-name.
	//std::cout << "Player collided with " << str << std::endl;

	if (other->getFaction() == EntityFaction::ENEMY && other->getType() != EntityType::EFFECT)
	{
		mGame->add(new ExplosionEntity(mGame, mSprite.getPosition()));
		mGame->remove(this);
	}

}

Vector2f ShipEntity::input()
{
	Vector2f input;
	if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		input.y = -1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		input.y = 1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		input.x = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		input.x = -1;
	}
	return input;
}

void ShipEntity::constrainPosition(Vector2f& input)
{
	if (input.x > 0 && getPosition().x > mGame->getRenderWindow().getSize().x - mRadius)
	{
		input.x = 0;
	}
	else if (input.x < 0 && getPosition().x < mRadius)
	{
		input.x = 0;
	}
	if (input.y > 0 && getPosition().y > mGame->getRenderWindow().getSize().y - mRadius)
	{
		input.y = 0;
	}
	else if (input.y < 0 && getPosition().y < mRadius)
	{
		input.y = 0;
	}
}

void ShipEntity::handleMovement(Vector2f input, float deltaTime)
{
	mSprite.move(input * mVelocity * deltaTime);
}

void ShipEntity::handleFire(float deltaTime)
{
	if (mFireDelta < mFireTime)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Space))
		{
			for (int i = 0; i < mFirePwr; i++)
			{
				BulletEntity* bullet = new BulletEntity(mGame, getPosition(), mBulletDirs[i], mFaction);
			}

			mFireTime = 0;
		}
	}
	else
		mFireTime += deltaTime;
}

void ShipEntity::addFirePower()	//Called when player picks up a pwr-up.
{
	mFirePwr += 2;
	mBulletDirs = getBulletDirs(mFirePwr, -45.0f);
}

void ShipEntity::decreaseFirePower()	//Called when player picks up a pwr-down debuff.
{
	mFirePwr -= 2;
	mBulletDirs = getBulletDirs(mFirePwr, -45.0f);
}

///<summary>
///<para>Calculates the direction of each bullet.</para>
///<para>Each bullet should be *delta* degrees apart (with the first and last bullets having an offset from 0 and 180 degrees).</para>
///<para>One bullet is always fired straight ahead.</para>
///</summary>
///<param name='max'>
///Number of shots the player ship shoots.
///</param>
///<param name='offsetDegrees'>
///Degrees by which the function offsets the outer-most bullets (first and last).
///</param>
vector<Vector2f> ShipEntity::getBulletDirs(int max, float offsetDegrees)
{
	vector<Vector2f> directions;
	if (max % 2 == 0)
	{
		cout << "Error. mFirePwr should always be an uneven number." << endl;
	}
	float deltaTo90 = (90 - offsetDegrees) / max;
	int medianIndex = ceil(max * 0.5f);
	float median = medianIndex * deltaTo90 + offsetDegrees; //gets the middle value
	float offset = 90 - median;	//the offset required to make the centered bullet fire at a 90 degree angle.

	for (int i = 0; i < max; i++)
	{
		float angle = 0;
		Vector2f direction;

		if (i == medianIndex - 1)	//Skip making calculations since we know that the bullet is supposed to go straight ahead.
		{
			direction = Vector2f(0, -1);	//Worth it?
		}
		else	//These calculations makes sure that the middle shot is always centered (shot at 90 degress or at direction (0, -1), and the rest are evenly distrubuted around 90 degrees.
		{
			angle = i * deltaTo90 + offsetDegrees + deltaTo90;
			angle += offset;

			float radians = angle * 3.1416 / 180.0f;
			direction = Vector2f((float)cos(radians), -(float)sin(radians));	//Convert from (float) degrees to a normalized Vector2f.
		}
		directions.push_back(direction);
	}
	return directions;
}