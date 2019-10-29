#include "BulletEntity.h"

namespace
{
	const float RADIUS = 4.0f;
	const float VELOCITY = 500.0f;
}

BulletEntity::BulletEntity(Game* game, Vector2f position, Vector2f direction, EntityFaction faction) :
	Entity(game, "Bullet.psd", position, RADIUS, EntityType::PROJECTILE, faction),
	mDirection(direction),
	mVelocity(VELOCITY)
{
	//setRotation();
	mGame->add(this);
}

void BulletEntity::update(float deltaTime)
{
	if(isOutOfBounds())
	{
		mGame->remove(this);
	}

	mSprite.move(mVelocity * mDirection * deltaTime);

	Entity::update(deltaTime);
}

void BulletEntity::collide(Entity* other)
{
	if (other->getFaction() != mFaction && other->getType() == EntityType::SHIP)	//Destroy other if other is not part of same faction as the bullet.
	{
		cout << "bullet hit its target" << endl;
		mGame->remove(this);
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
	//arg(z) = tan - 1(y / x)
	mSprite.setRotation(atan(mDirection.y / mDirection.x));	//Test/Debug this..
}

BulletEntity::~BulletEntity()
{
	cout << "destroyed bullet" << endl;
}
