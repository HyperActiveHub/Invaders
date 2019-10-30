#include "ExplosionEntity.h"

namespace
{
	const float ANIMATION_FPS = 16.0f;
}

ExplosionEntity::ExplosionEntity(Game* game, Vector2f position, EntityFaction faction) :
	Entity(game, "ExplosionSheet.png", position, 0, EntityType::EFFECT, faction),
	mTime(0),
	sourceRect(0, 0, 92, 92)
{
	mSprite.setTextureRect(sourceRect);
	centerSprite();
	randRotation();
}

void ExplosionEntity::update(float deltaTime)
{
	mTime += deltaTime;
	if (mTime > 1 / ANIMATION_FPS)
	{
		mTime = 0;
		sourceRect.left += sourceRect.width;
		mSprite.setTextureRect(sourceRect);
	}
	
	if (sourceRect.left == sourceRect.width * 5 && mTime == 0)
	{
		die();

		if (mFaction == EntityFaction::FRIEND)
		{
			mGame->GameOver();
		}
	}
}

void ExplosionEntity::collide(Entity* entity)
{
	if (entity->getType() == EntityType::SHIP && entity->getFaction() == EntityFaction::FRIEND)
	{
		//kill player
	}
}

void ExplosionEntity::randRotation()
{
	int angle = rand() % 360;
	mSprite.setRotation((float)angle);
}

ExplosionEntity::~ExplosionEntity()
{
	//cout << "Destroyed Explosion" << endl;
}