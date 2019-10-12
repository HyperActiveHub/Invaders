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

//void Entity::update(float deltaTime)
//{
//
//}

void Entity::centerSprite()
{
	mSprite.setOrigin(mSprite.getLocalBounds().width * 0.5f, mSprite.getLocalBounds().height * 0.5f);
}

void Entity::draw()
{
	mGame->getRenderWindow().draw(mSprite);
}

EntityFaction Entity::getFaction()
{
	return mFaction;
}

EntityType Entity::getType()
{	
	return mType;
}

float Entity::getRadius()
{
	return mRadius;
}

Vector2f Entity::getPosition()
{
	return mSprite.getPosition();
}

void Entity::collide(Entity* other)
{
	//Empty?
}

void Entity::update(float deltaTime)
{
	//Move or empty?
}