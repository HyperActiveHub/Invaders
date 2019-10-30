#include "BulletEntity.h"

namespace
{
	const float RADIUS = 4.0f;
	const float VELOCITY = 500.0f;
}

BulletEntity::BulletEntity(Game* game, Vector2f position, Vector2f direction, EntityFaction faction) :
	Entity(game, "Bullet.png", position, RADIUS, EntityType::PROJECTILE, faction),
	mDirection(direction),
	mVelocity(VELOCITY)
{
	setRotation();
	setColor();
	mGame->add(this);

	//Every bullet costs the player some score (10?). This makes the player think before he shoots instead of spamming. This also makes the player consider if he should pick up a pwr-up.
	if (faction == EntityFaction::FRIEND)
	{
		mGame->decreaseScore();
	}
}

void BulletEntity::update(float deltaTime)
{
	if(isOutOfBounds())
	{
		mGame->remove(this);
	}

	mSprite.move(mVelocity * mDirection * deltaTime);
}

void BulletEntity::collide(Entity* other)
{
	if (other->getFaction() != mFaction && other->getType() == EntityType::SHIP)	//Destroy hit ship if its not part of same faction as the bullet.
	{
		die();
	}
}

bool BulletEntity::isOutOfBounds()
{
	if (getPosition().x > mRadius + mGame->getRenderWindow().getSize().x)
	{
		return true;
	}
	else if (getPosition().x < -mRadius)
	{
		return true;
	}
	if (getPosition().y > mRadius + mGame->getRenderWindow().getSize().y)
	{
		return true;
	}
	else if (getPosition().y < -mRadius)
	{
		return true;
	}
	return false;
}

void BulletEntity::setRotation()	//Makes the bullet rotate toward the direction its being shot in.
{
	//arg(z) = arctan(y / x)
	double radians = atan(mDirection.y / mDirection.x);
	double angle = 90 + radians * 180 / 3.1416;
	mSprite.setRotation((float)angle);
}

void BulletEntity::setColor()
{
	switch (mFaction)
	{
	case EntityFaction::FRIEND:
		mSprite.setColor(Color::Green);
		break;

	case EntityFaction::ENEMY:
		mSprite.setColor(Color::Red);
		break;
	}
}

BulletEntity::~BulletEntity()
{
	//cout << "destroyed bullet" << endl;
}