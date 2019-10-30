#pragma once
#include "Entity.h"

enum class PickupType { PowerUp, PowerDown, Count };

class PickupEntity : public Entity
{
public:
	PickupEntity(Game* game, Vector2f position, PickupType type);
	static PickupType getRandPickup();
	virtual void collide(Entity* other) override;
	virtual void update(float deltaTime) override;
	~PickupEntity();

private:

	int mVelocity;
	string getSpriteName(PickupType type);
	float getRadius(PickupType type);
	int getRandVelocity();
	PickupType mPickupType;
};

