#pragma once
#include "Entity.h"

class BulletEntity : public Entity
{
public:
	BulletEntity(Game* game, Vector2f position, Vector2f direction, EntityFaction faction);
	~BulletEntity();
	virtual void update(float deltaTime) override;
	virtual void collide(Entity* other) override;

	void setDirection(Vector2f dir);

private:
	float mVelocity;
	Vector2f mDirection;

	bool isOutOfBounds();
	void setRotation();
};

