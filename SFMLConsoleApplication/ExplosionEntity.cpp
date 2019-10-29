#include "ExplosionEntity.h"

namespace
{
	const float EXPLOSION_DELTA = 0.15f;
}

ExplosionEntity::ExplosionEntity(Game* game, Vector2f position) : 
	Entity(game, "Explosion.psd", position, 0, EntityType::EFFECT, EntityFaction::NEUTRAL),
	mTime(0)
{

}

void ExplosionEntity::update(float deltaTime)
{
	//Show sprite for a set amount of time
	
	mTime += deltaTime;
	if (mTime > EXPLOSION_DELTA)
	{
		mGame->remove(this);
	}

	Entity::update(deltaTime);
}

void ExplosionEntity::collide(Entity* entity)
{
	//do nothing?
}
