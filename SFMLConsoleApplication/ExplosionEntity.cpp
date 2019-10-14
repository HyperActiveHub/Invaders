#include "ExplosionEntity.h"



ExplosionEntity::ExplosionEntity(Game* game, Vector2f position) : 
	Entity(game, "Explosion.psd", position, 0, EntityType::EFFECT, EntityFaction::NEUTRAL)
{

}

void ExplosionEntity::update(float deltaTime)
{
	//Show sprite for a set amount of time
	Entity::update(deltaTime);
}

void ExplosionEntity::collide(Entity* entity)
{
	//do nothing?
}
