#pragma once
#include "Entity.h"

class ExplosionEntity : public Entity
{
public:
	ExplosionEntity(Game* game, Vector2f position, EntityFaction faction);
	~ExplosionEntity();
private:
	virtual void update(float deltaTime) override;
	virtual void collide(Entity*) override;
	float mTime;
	IntRect sourceRect;
	void randRotation();
};

