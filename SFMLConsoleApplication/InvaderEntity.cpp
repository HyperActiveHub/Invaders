#include "InvaderEntity.h"
#include "ExplosionEntity.h"
#include "BulletEntity.h"
#include "PickupEntity.h"

using namespace std;
using namespace sf;

namespace
{
	const float RADIUS = 32.0f;
	const float VELOCITY = 200.0f;
	const float FIRE_DELTA = 0.855f;
	const float DROP_RATE = 10;	//10% drop chance.
}

InvaderEntity::InvaderEntity(Game* game, Vector2f position, Vector2f direction) :
	Entity(game, "Invader.psd", position, RADIUS, EntityType::SHIP, EntityFaction::ENEMY),
	mFireDelta(FIRE_DELTA),
	mFireTime(0.0f),
	mDirection(direction),
	mVelocity(VELOCITY)
{

}

InvaderEntity::~InvaderEntity()
{
	//cout << "Destroyed Invader" << endl;
}

void InvaderEntity::update(float deltaTime)
{
	handleMovement(deltaTime);
	handleFire(deltaTime);	
}

void InvaderEntity::collide(Entity* other)
{
	if (other->getFaction() == EntityFaction::FRIEND)
	{
		switch (other->getType())
		{
		case EntityType::SHIP:
			//destroy player ship. Do nothing.
			break;

		case EntityType::PROJECTILE:
			mGame->increaseScore();
			dropPickup();
			die();
			break;
		}
	}

}

void InvaderEntity::handleMovement(float deltaTime)
{
	if (getPosition().y > mRadius + mGame->getRenderWindow().getSize().y)	//Destroy invader when out of bounds (will only happen when it reaches the bottom of the window).
	{
		mGame->remove(this);
	}

	//Bounce off the walls
	if (mDirection.x > 0 && mGame->getRenderWindow().getSize().x < getPosition().x + mRadius)
	{
		mDirection.x *= -1;
	}
	else if (mDirection.x < 0 && getPosition().x - mRadius < 0)
	{
		mDirection.x *= -1;
	}

	mSprite.move(mDirection * mVelocity * deltaTime);
}

void InvaderEntity::handleFire(float deltaTime)
{
	mFireTime += deltaTime;
	if (mFireDelta < mFireTime)
	{
		BulletEntity* bullet = new BulletEntity(mGame, getPosition(), Vector2f(0, 1), mFaction);
		mFireTime = 0;
	}
}

void InvaderEntity::dropPickup()
{
	int dropChance = rand() % 100 + 1;

	if (dropChance <= DROP_RATE)
	{
		PickupEntity* pickup = new PickupEntity(mGame, getPosition(), PickupEntity::getRandPickup());
	}
}

void InvaderEntity::die()
{
	mGame->add(new ExplosionEntity(mGame, mSprite.getPosition(), mFaction));
	Entity::die();
}