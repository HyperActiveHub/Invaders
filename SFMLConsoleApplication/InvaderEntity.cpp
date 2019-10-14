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
	//Bounce of walls whilst moving downward
}

void InvaderEntity::handleFire(float deltaTime)
{
	mFireTime += deltaTime;
	if (mFireDelta < mFireTime)
	{
		//fire again
	}
}
