#include "Entity.h"

using namespace std;

Entity::Entity(Game* game, string filename, Vector2f position, float radius, EntityType type, EntityFaction faction) :
	mGame(game),
	mSprite(game->getTexture(filename)),
	mRadius(radius),
	mType(type),
	mFaction(faction)
{
	centerSprite();
	mSprite.setPosition(position);
}

void Entity::update(float deltaTime)
{

}

void Entity::collide(Entity* other)
{
	
}
