#include "InvaderEntity.h"
#include "ExplosionEntity.h"

using namespace std;
using namespace sf;

namespace 
{
	const float RADIUS = 32.0f;
	const float FIRE_DELTA = 0.5f;
	const float VELOCITY = 200.0f;
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
	cout << "Destroyed Invader" << endl;
}

void InvaderEntity::update(float deltaTime)
{
	handleMovement(deltaTime);
	handleFire(deltaTime);

	Entity::update(deltaTime);
}

void InvaderEntity::collide(Entity* other)
{
	if (other->getFaction() == EntityFaction::FRIEND)
	{
		mGame->add(new ExplosionEntity(mGame, mSprite.getPosition()));
		mGame->remove(this);
	}
}

void InvaderEntity::handleMovement(float deltaTime)
{
	if (getPosition().y > mGame->getRenderWindow().getSize().y)	//Destroy invader when out of bounds (will only happen when it reaches the bottom of the window).
	{
		mGame->remove(this);
	}
	
	//Bounce of walls
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
		//fire again
	}
}
